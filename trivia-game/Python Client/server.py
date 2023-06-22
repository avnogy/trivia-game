import socket


class Server:
    def __init__(self, server_ip, server_port):
        #creating socket
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        #connecting socket to server
        self.socket.connect((server_ip, server_port))

    def send(self, code, message):
        """
        Sending a message to the server.
        The message protocol is:
            <code - 1 byte><message length - 4 bytes><message - x bytes>

        :param code <byte>: the code-type of the message
        :param message <str>: the message to send

        :return <bytes - encoded string>: encoded message according to protocol
        """
        self.socket.send(f'{code}{str(len(message)).zfill(4)}{message}'.encode())