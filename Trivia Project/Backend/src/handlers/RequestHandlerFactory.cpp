#include "handlers/RequestHandlerFactory.h"

/// <summary>
/// Creating a new loginRequestHandler
/// </summary>
/// <returns>pointer to a new loginRequestHandler</returns>
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() const
{
	return new LoginRequestHandler();
}

/// <summary>
/// Creatign a new menuRequestHandler
/// </summary>
/// <param name="user">user that logged in and want to go to the menu</param>
/// <returns>a new instance of menuRequestHandler</returns>
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& user) const
{
	return new MenuRequestHandler(user);
}