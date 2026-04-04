import socket
import threading
import json
from client_manager import GestorClientes
from protocol import Protocolo

class ServidorIoT:
    def __init__(self, host='0.0.0.0', puerto=5000):
        self.host = host
        self.puerto = puerto
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.gestor = GestorClientes()

    def iniciar(self):
        self.server.bind((self.host, self.puerto))
        self.server.listen(5)
        print(f"Servidor IoT iniciado en {self.host}:{self.puerto}")
        print("-" * 50)

        while True:
            cliente_socket, direccion = self.server.accept()
            threading.Thread(
                target=self.manejar_cliente,
                args=(cliente_socket, direccion),
                daemon=True
            ).start()

    def manejar_cliente(self, socket_cliente, direccion):
        buffer = ""
        try:
            while True:
                datos = socket_cliente.recv(1024).decode()
                if not datos:
                    break

                buffer += datos
                while "\n" in buffer:
                    linea, buffer = buffer.split("\n", 1)
                    self.procesar_mensaje(linea, socket_cliente)
        except:
            pass
        finally:
            self.gestor.eliminar(socket_cliente)
            socket_cliente.close()

    def procesar_mensaje(self, data, socket_cliente):
        try:
            mensaje = json.loads(data)
        except:
            return

        tipo = mensaje.get("tipo")

        if tipo == "registro":
            self.gestor.registrar(
                mensaje.get("id"),
                socket_cliente,
                None,
                mensaje.get("dispositivo_tipo")
            )

        elif tipo == "sensor_data":
            distancia = mensaje.get("distancia")
            
            if distancia < 10:
                color = "ROJO"
                rgb = [255, 0, 0]
                duracion = 1000
            elif 10 <= distancia <= 20:
                color = "AZUL"
                rgb = [0, 0, 255]
                duracion = 500
            elif 20 <= distancia <= 30:
                color = "VERDE"
                rgb = [0, 255, 0]
                duracion = 200
            else:
                color = "APAGADO"
                rgb = [0, 0, 0]
                duracion = 100
            
            print(f"{color:8} | {distancia:5.1f} cm")
            
            comando = Protocolo.comando_led(rgb, duracion)
            self.enviar_a_actuadores(comando)

    def enviar_a_actuadores(self, comando):
        for cliente in self.gestor.obtener_actuadores():
            try:
                cliente.socket.send((json.dumps(comando) + "\n").encode())
            except:
                pass