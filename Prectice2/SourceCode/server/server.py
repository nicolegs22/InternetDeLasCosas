
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
        print(f"Servidor en {self.host}:{self.puerto}")

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
                    self.procesar_mensaje(linea, socket_cliente, direccion)
        finally:
            self.gestor.eliminar(socket_cliente)
            socket_cliente.close()

    def procesar_mensaje(self, data, socket_cliente, direccion):
        try:
            mensaje = json.loads(data)
        except:
            return

        tipo = mensaje.get("tipo")
        id = mensaje.get("id")

        if tipo == "registro":
            self.gestor.registrar(
                id,
                socket_cliente,
                direccion,
                mensaje.get("dispositivo_tipo")
            )

        elif tipo == "sensor_data":
            distancia = mensaje.get("distancia")
            print(f"[SENSOR] {id}: {distancia} cm")

            comando = self.evaluar_distancia(distancia)
            self.enviar_a_actuadores(comando)

        elif tipo == "comando_respuesta":
            print(f"[ACTUADOR OK] {id}: {mensaje.get('comando')}")

    def evaluar_distancia(self, d):
        if d < 50:
            return Protocolo.comando_led("rojo", 1000)
        elif d < 100:
            return Protocolo.comando_led("amarillo", 500)
        else:
            return Protocolo.comando_led("verde", 200)

    def enviar_a_actuadores(self, comando):
        for cliente in self.gestor.obtener_actuadores():
            try:
                cliente.socket.send((json.dumps(comando) + "\n").encode())
                print(f"[→] Enviado a {cliente.id}")
            except Exception as e:
                print(f"Error: {e}")