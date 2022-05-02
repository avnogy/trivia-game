#pragma once
#include "server/Socket.h"
#include "handlers/IRequestHandler.h"
#include <map>
#include "requests/LoginRequest.h"
#include "json/JsonRequestPacketDeserializer.h"

//delete when we'll develop request handlers
#include "handlers/LoginRequestHandler.h"

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
