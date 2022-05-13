#pragma once

#include "managers/LoginManager.h"
#include "database/SqliteDataBase.h"
#include "handlers/LoginRequestHandler.h"
#include "utils/Singleton.h"

class LoginRequestHandler;

class LoginRequestHandler;

class RequestHandlerFactory
{
	MAKE_SINGLETON(RequestHandlerFactory);
	DELETE_CONSTRUCTOR(RequestHandlerFactory);

public:
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
};
