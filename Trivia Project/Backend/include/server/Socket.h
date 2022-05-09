#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#include <vector>
#include "server/SocketError.h"

class Socket
{
private:
	using port = unsigned short;
	using ip = const std::string&;

	SOCKET m_socket;

	Socket(SOCKET socket);

public:
	//C'tors
	Socket();
	~Socket();

	//Server methods
	void bind(port port);
	void listen();
	Socket* accept();

	//Client methods
	void connect(ip ip, port port);

	//General methods
	std::string recvString(const size_t expectedSize);
	std::vector<unsigned char> recvBuffer(const size_t expectedSize);
	void send(const std::string& message);
	void send(const std::vector<unsigned char>& buffer);

	bool operator<(const Socket& otherSocket) const;
};
