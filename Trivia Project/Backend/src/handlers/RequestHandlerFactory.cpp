#include "handlers/RequestHandlerFactory.h"

/// <summary>
/// Instantiating a new RequestHandlerFactory
/// </summary>
/// <param name="database">pointer to database</param>
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
	m_database(database), m_loginManager(database)
{
}

/// <summary>
/// Creating a new loginRequestHandler
/// </summary>
/// <returns>pointer to a new loginRequestHandler</returns>
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(LoginManager::instance(), this);
}