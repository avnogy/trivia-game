#pragma once
#include "infrastructure/Communicator.h"
#include "infrastructure/database/IDatabase.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "utils/Singleton.h"

class Server
{
	MAKE_SINGLETON(Server);
	DELETE_CONSTRUCTOR(Server);

public:
	void run();
};
