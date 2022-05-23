#pragma once
#include "infrastructure/Communicator.h"
#include "infrastructure/database/IDatabase.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "utils/Singleton.h"

#define DATABASE_FILE_PATH "D:/Coding/magshimim/Advanced-Programming/trivia-project/Trivia Project/database.sqlite"

#define DATABASE_PATH "D:/Coding/magshimim/Advanced-Programming/trivia-project/Trivia Project/database.sqlite"

class Server
{
	MAKE_SINGLETON(Server);
	DELETE_CONSTRUCTOR(Server);

public:
	void run();
};
