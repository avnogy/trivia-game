from server import Server

def main():
    print(" ----- python client ----- ")

    #conneting to server
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.connect(('127.0.0.1', 4206))

    server.send(MESSAGE.encode())


if __name__ == '__main__':
    main()