#pragma once
#include "server/Socket.h"
#include "handlers/IRequestHandler.h"
#include <map>
#include <ctime>
#include "requests/LoginRequest.h"
#include "json/JsonRequestPacketDeserializer.h"
#include "json/JsonRequestPacketSerializer.h"
#include "handlers/LoginRequestHandler.h"
#include "handlers/RequestHandlerFactory.h"

#define PORT 4206

class Communicator
{
private:
	Socket m_serverSocket;
	std::map<Socket*, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;

	RequestInfo recvRequest(Socket& socket);

	void bindAndListen();
	void handleNewClient(Socket** socket);
public:
	Communicator(RequestHandlerFactory& handlerFactory);

	void startHandleRequest();
};
