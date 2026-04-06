from server import ServidorIoT

if __name__ == "__main__":
    servidor = ServidorIoT()
    try:
        servidor.iniciar()
    except KeyboardInterrupt:
        print("Cerrando servidor...")