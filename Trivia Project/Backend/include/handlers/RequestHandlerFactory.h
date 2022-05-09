#pragma once

#include "managers/LoginManager.h"
#include "database/SqliteDataBase.h"
#include "handlers/LoginRequestHandler.h"

class RequestHandlerFactory
{
private:
	LoginManager m_loginManager;
	IDatabase* m_database;

public:
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManager();
};
