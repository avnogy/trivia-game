#include "handlers/RoomMemberRequestHandler.h"

/// <summary>
/// Leaving the room
/// </summary>
/// <param name="requestInfo">information about result</param>
/// <returns>response and next handler</returns>
RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& requestInfo)
{
	bool result = m_room.removeUser(m_user);

	ReturnNewRequestResult(
		SERIALIZE(LeaveRoomResponse{result ? LeaveRoomResponse::SUCCESS : LeaveRoomResponse::FAILURE}),
		(IRequestHandler*)RequestHandlerFactory::instance().createMenuRequestHandler(m_user)
	);
}

/// <summary>
/// Leaves room and logs user out
/// </summary>
/// <param name="requestInfo"></param>
/// <returns></returns>
RequestResult RoomMemberRequestHandler::logout(const RequestInfo& requestInfo)
{
	leaveRoom(requestInfo);
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
bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (requestInfo.id)
	{
	case IDS::LeaveRoomRequest: case IDS::GetRoomStateRequest: case IDS::GetPlayersInRoomRequest: case IDS::LogoutRequest:
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
RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (requestInfo.id)
	{
	case IDS::LeaveRoomRequest:
		return leaveRoom(requestInfo);

	case IDS::GetRoomStateRequest:
		return getRoomState(requestInfo);

	case IDS::GetPlayersInRoomRequest:
		return getPlayersInRoom(requestInfo);

	case IDS::LogoutRequest:
		return logout(requestInfo);

	}
}

/// <summary>
/// Create a new RoomMember handler
/// </summary>
RoomMemberRequestHandler::RoomMemberRequestHandler(Room& room, const LoggedUser& user) :
	IRoomMemberRequestHandler(room, user)
{
}
