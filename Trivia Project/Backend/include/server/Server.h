#pragma once
#include "server/Communicator.h"
#include "database/IDatabase.h"
#include "handlers/RequestHandlerFactory.h"

class Server
{
private:
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
public:
	Server();
	void run();
};
