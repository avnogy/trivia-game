#include "handlers/RequestHandlerFactory.h"

/// <summary>
/// Instantiating a new RequestHandlerFactory
/// </summary>
/// <param name="database">database</param>
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) :
	m_database(database)
{
}

/// <summary>
/// Creating a new loginRequestHandler
/// </summary>
/// <returns>pointer to a new loginRequestHandler</returns>
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(m_loginManager, this);
}

/// <summary>
/// Getting to m_loginManager
/// </summary>
/// <returns>m_loginManager</returns>
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}