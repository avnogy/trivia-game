#include "Socket.h"
#pragma warning(disable:4996)

/// <summary>
/// Creating a new Socket object from a WINAPI's "SOCKET".
/// </summary>
/// <param name="socket">WINAPI's "SOCKET" to create an object from</param>
Socket::Socket(SOCKET socket) :
	m_socket(socket)
{
}

/// <summary>
/// Creating a new socket
/// </summary>
Socket::Socket() :
	m_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (m_socket == INVALID_SOCKET)
		throw SocketError("Unable to create socket");
}

/// <summary>
/// Destroying this socket
/// </summary>
Socket::~Socket()
{
	if (closesocket(m_socket) == SOCKET_ERROR)
		throw SocketError("Unable to close socket");
}

/// <summary>
/// Binding this socket with a certain port
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
/// Start listenning to new connection
/// </summary>
void Socket::listen()
{
	if (::listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

/// <summary>
/// Accepting a new connection
/// </summary>
/// <returns>Socket of new connection</returns>
Socket* Socket::accept()
{
	SOCKET client = ::accept(m_socket, NULL, NULL);

	if (client == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - accept");

	return new Socket(client);
}

/// <summary>
/// Making a connection between this socket and a server
/// </summary>
/// <param name="ip">server's ip</param>
/// <param name="port">server's port</param>
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
/// Receiving a message from this socket
/// </summary>
/// <param name="expectedSize">amount of bytes to receive</param>
/// <returns>string representing the received message</returns>
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
/// Sending a message to this socket
/// </summary>
/// <param name="message">Message to send</param>
void Socket::send(const std::string& message)
{
	if (::send(m_socket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - send");
}

/// <summary>
/// This method is being used so the Socket can be a map key
/// </summary>
/// <param name="otherSocket">other socket to compare this socket to</param>
/// <returns>how to order the sockets</returns>
bool Socket::operator<(const Socket& otherSocket) const
{
	return m_socket < otherSocket.m_socket;
}