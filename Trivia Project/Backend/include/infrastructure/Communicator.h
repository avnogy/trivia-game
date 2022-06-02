#pragma once
#include "infrastructure/Socket.h"
#include "handlers/IRequestHandler.h"
#include <unordered_map>
#include <ctime>
#include "requests/LoginRequest.h"
#include "infrastructure/json/JsonRequestPacketDeserializer.h"
#include "infrastructure/json/JsonRequestPacketSerializer.h"
#include "handlers/LoginRequestHandler.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "utils/Singleton.h"
#include "handlers/IRequestHandler.h"

#define PORT 4206

class Communicator
{
	MAKE_SINGLETON(Communicator);
	DELETE_CONSTRUCTOR(Communicator);

private:
	Socket m_serverSocket;
	std::unordered_map<Socket*, IRequestHandler*> m_clients;

	RequestInfo recvRequest(Socket& socket);
	void bindAndListen();
	void handleNewClient(Socket* socket);

public:
	std::unordered_map<std::string, Socket*> usernameToSocket;
	void startHandleRequest();
	void bindUsernameToSocket(const std::string& username, IRequestHandler* requestHandler);
};
