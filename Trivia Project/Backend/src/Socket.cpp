#include "Socket.h"
#pragma warning(disable:4996)

Socket::Socket(SOCKET socket) :
	m_socket(socket)
{
}

Socket::Socket() :
	m_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	if (m_socket == INVALID_SOCKET)
		throw SocketError("Unable to create socket");
}

Socket::~Socket()
{
	if (closesocket(m_socket) == SOCKET_ERROR)
		throw SocketError("Unable to close socket");
}

void Socket::bind(port port)
{
	sockaddr_in sa = { 0 };
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;

	if (::bind(m_socket, (sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
}

void Socket::listen()
{
	if (::listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

Socket Socket::accept()
{
	SOCKET client = ::accept(m_socket, NULL, NULL);

	if (client == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - accept");

	return Socket(client);
}

void Socket::connect(ip ip, port port)
{
	sockaddr_in sa = { 0 };
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ip.c_str());

	if (::connect(m_socket, (struct sockaddr*)&sa, sizeof(sa)) == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - connect");
}

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

void Socket::send(const std::string& message)
{
	if (::send(m_socket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - send");
}