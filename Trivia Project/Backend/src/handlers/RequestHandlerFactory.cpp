#include "handlers/RequestHandlerFactory.h"

/// <summary>
/// Creating a new loginRequestHandler
/// </summary>
/// <returns>pointer to a new loginRequestHandler</returns>
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(LoginManager::instance(), this);
}