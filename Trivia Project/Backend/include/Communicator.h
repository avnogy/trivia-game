#pragma once
#include "Socket.h"
#include "IRequestHandler.h"
#include <map>
#include "LoginRequest.h"
#include "JsonRequestPacketDeserializer.h"

//delete when we'll develop request handlers
#include "LoginRequestHandler.h"

#define PORT 4206

class Communicator
{
private:
	Socket m_serverSocket;
	std::map<Socket*, IRequestHandler*> m_clients;

	void bindAndListen();
	void handleNewClient(Socket** socket);
public:
	void startHandleRequest();
};
