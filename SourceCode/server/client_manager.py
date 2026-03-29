from datetime import datetime

class Cliente:
    def __init__(self, id, socket, direccion, tipo):
        self.id = id
        self.socket = socket
        self.direccion = direccion
        self.tipo = tipo
        self.conectado = datetime.now()

class GestorClientes:
    def __init__(self):
        self.clientes = {}

    def registrar(self, id, socket, direccion, tipo):
        self.clientes[id] = Cliente(id, socket, direccion, tipo)
        print(f"[+] Registrado {id} ({tipo})")

    def eliminar(self, socket):
        for id, cliente in list(self.clientes.items()):
            if cliente.socket == socket:
                del self.clientes[id]
                print(f"[-] Desconectado {id}")

    def obtener_actuadores(self):
        return [c for c in self.clientes.values() if c.tipo == "actuador"]