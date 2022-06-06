#include "infrastructure/RequestHandlerFactory.h"

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

/// <summary>
/// Create a new RoomAdminRequestHandler
/// </summary>
/// <param name="room">the room the admin created</param>
/// <param name="user">the admin</param>
/// <returns>new handler</returns>
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const Room& room, const LoggedUser& user) const
{
	return new RoomAdminRequestHandler(room, user);
}

/// <summary>
/// Create a new RoomMemberRequestHandler
/// </summary>
/// <param name="room">the room the member joined</param>
/// <param name="user">the member</param>
/// <returns>new handler</returns>
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const Room& room, const LoggedUser& user) const
{
	return new RoomMemberRequestHandler(room, user);
}
