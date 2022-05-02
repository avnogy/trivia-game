from server import Server
import json

def main():
    print(" ----- python client ----- ")

    #conneting to server
    server = Server('127.0.0.1', 4206)

    content = {
        "username": "Donald Trump",
        "password": "123456"
        }

    server.send(1, json.dumps(content))


if __name__ == '__main__':
    main()