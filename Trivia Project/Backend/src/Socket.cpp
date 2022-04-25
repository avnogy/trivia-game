#include "Socket.h"
#pragma warning(disable:4996)


/// <summary>
/// Encapsulating an existing winapi SOCKET
/// </summary>
/// <param name="socket">winapi socket to encapsulate</param>
Socket::Socket(SOCKET socket) :
	m_socket(socket)
{
}


/// <summary>
/// Creating a new Socket
/// </summary>
Socket::Socket() :
	m_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (m_socket == INVALID_SOCKET)
		throw SocketError("Unable to create socket");
}


/// <summary>
/// Destroying an existing Socket
/// </summary>
Socket::~Socket()
{
	if (closesocket(m_socket) == SOCKET_ERROR)
		throw SocketError("Unable to close socket");
}

/// <summary>
/// Connecting Socket to a specific port
/// </summary>
/// <param name="port">port to bind this socket to</param>
void Socket::bind(port port)
{
	sockaddr_in sa = { 0 };
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	if (::bind(m_socket, (sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
}


/// <summary>
/// Start to wait for new connections
/// </summary>
void Socket::listen()
{
	if (::listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

/// <summary>
/// Accepting a standby client
/// </summary>
/// <returns>Socket representing the new client accepted</returns>
Socket Socket::accept()
{
	SOCKET client = ::accept(m_socket, NULL, NULL);

	if (client == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - accept");

	return Socket(client);
}

/// <summary>
/// Connecting his socket to a server socket
/// </summary>
/// <param name="ip">ip of the server</param>
/// <param name="port">port the server listenning to</param>
void Socket::connect(ip ip, port port)
{
	sockaddr_in sa = { 0 };
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ip.c_str());

	if (::connect(m_socket, (struct sockaddr*)&sa, sizeof(sa)) == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - connect");
}

/// <summary>
/// Receive messages from this socket.
/// </summary>
/// <param name="expectedSize">the expected size of the incomming message</param>
/// <returns>a string representing the received message</returns>
std::string Socket::recv(const size_t expectedSize)
{
	char* buffer = new char[expectedSize + 1];
	std::string message;

	buffer[expectedSize] = NULL;

	if (::recv(m_socket, buffer, expectedSize, 0) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - recv");

	message = buffer;

	delete[] buffer;
	return message;
}


/// <summary>
/// Sending a message to this socket.
/// </summary>
/// <param name="message">string representing the message to send</param>
void Socket::send(const std::string& message)
{
	if (::send(m_socket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - send");
}



/// <summary>
/// Overloading the < operator so this class can be used as a map key
/// </summary>
/// <param name="otherSocket">another socket to compare to this socket</param>
/// <returns>whether this socket should go before the other socket (in the map order)</returns>
bool Socket::operator<(const Socket& otherSocket) const
{
	return m_socket < otherSocket.m_socket;
}
