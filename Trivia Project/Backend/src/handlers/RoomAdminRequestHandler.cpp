#include "handlers/RoomAdminRequestHandler.h"

/// <summary>
/// closing room  - telling all room members to leave
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and new handler</returns>
RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& requestInfo) const
{
	for (auto& user : m_room.getAllUsers())
	{
		//if user is this user, continue
		if (user == m_user.getUsername())
			continue;

		//accesing the users socket
		Socket* userSocket = Communicator::instance().getSocket(user);

		//creating a new handler to user
		IRequestHandler* newRequestHandler = RequestHandlerFactory::instance().createMenuRequestHandler(user);

		//sending user a start game message
		userSocket->send(SERIALIZE((UpdateResponse{ UpdateResponse::SUCCESS, UpdateResponse::LeaveRoom })));

		//replacing user's handler
		Communicator::instance().setRequestHandler(user, newRequestHandler);
	}

	RoomManager::instance().deleteRoom(m_room.getRoomData().id);

	ReturnNewRequestResult(
		SERIALIZE(CloseRoomResponse{CloseRoomResponse::SUCCESS}),
		(IRequestHandler*)RequestHandlerFactory::instance().createMenuRequestHandler(m_user)
	);
}

/// <summary>
/// starting game  - telling all room members to start
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and new handler</returns>
RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& requestInfo) const
{
	std::shared_ptr<Game> game( GameManager::instance().createGame(m_room) );

	for (auto& user : m_room.getAllUsers())
	{
		//if user is this user, continue
		if (user == m_user.getUsername())
			continue;
		
		//accesing the users socket
		Socket* userSocket = Communicator::instance().getSocket(user);
		
		//creating a new handler to user
		IRequestHandler* newRequestHandler = RequestHandlerFactory::instance().createGameRequestHandler(game, user);

		//sending user a start game message
		userSocket->send(SERIALIZE((UpdateResponse{ UpdateResponse::SUCCESS, UpdateResponse::StartGame })));

		//replacing user's handler
		Communicator::instance().setRequestHandler(user, newRequestHandler);
	}

	RoomManager::instance().deleteRoom(m_room.getRoomData().id);

	ReturnNewRequestResult(
		SERIALIZE(StartGameResponse{StartGameResponse::SUCCESS}),
		(IRequestHandler*)RequestHandlerFactory::instance().createGameRequestHandler(game, m_user)
	);
}

/// <summary>
/// Closes room and logs out user
/// </summary>
/// <param name="requestInfo"></param>
/// <returns></returns>
RequestResult RoomAdminRequestHandler::logout(const RequestInfo& requestInfo)
{
	closeRoom(requestInfo);
	bool result = LoginManager::instance().logout(m_user.getUsername());
	ReturnNewRequestResult(
		SERIALIZE(LogoutResponse{ (unsigned int)(result == true ? LogoutResponse::SUCCESS : LogoutResponse::FAILURE) }),
		RequestHandlerFactory::instance().createLoginRequestHandler()
	);
}

/// <summary>
/// Checks whether the the request is relevant to this handler
/// </summary>
/// <param name="requestInfo">info about request</param>
/// <returns>whether relevant</returns>
bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (requestInfo.id)
	{
	case IDS::CloseRoomRequest: case IDS::StartGameRequest: case IDS::GetRoomStateRequest: case IDS::GetPlayersInRoomRequest: 	case IDS::LogoutRequest:
		return true;
	default:
		return false;
	}
}

/// <summary>
/// Calls the right function to handle the request
/// </summary>
/// <param name="requestInfo">info about request</param>
/// <returns>response and next handler</returns>
RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (requestInfo.id)
	{
	case IDS::CloseRoomRequest:
		return closeRoom(requestInfo);

	case IDS::StartGameRequest:
		return startGame(requestInfo);

	case IDS::GetPlayersInRoomRequest:
		return getPlayersInRoom(requestInfo);

	case IDS::GetRoomStateRequest:
		return getRoomState(requestInfo);

	case IDS::LogoutRequest:
		return logout(requestInfo);
	}
}

/// <summary>
/// Create a new RoomAdmin Handler
/// </summary>
RoomAdminRequestHandler::RoomAdminRequestHandler(Room& room, const LoggedUser& user) :
	IRoomMemberRequestHandler(room, user)
{
}
