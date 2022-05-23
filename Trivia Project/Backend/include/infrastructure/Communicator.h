#pragma once
#include "infrastructure/Socket.h"
#include "handlers/IRequestHandler.h"
#include <map>
#include <ctime>
#include "requests/LoginRequest.h"
#include "infrastructure/json/JsonRequestPacketDeserializer.h"
#include "infrastructure/json/JsonRequestPacketSerializer.h"
#include "handlers/LoginRequestHandler.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "utils/Singleton.h"

#define PORT 4206

class Communicator
{
	MAKE_SINGLETON(Communicator);
	DELETE_CONSTRUCTOR(Communicator);

private:
	Socket m_serverSocket;
	std::map<Socket*, IRequestHandler*> m_clients;

	RequestInfo recvRequest(Socket& socket);
	void bindAndListen();
	void handleNewClient(Socket** socket);

public:
	void startHandleRequest();
};
