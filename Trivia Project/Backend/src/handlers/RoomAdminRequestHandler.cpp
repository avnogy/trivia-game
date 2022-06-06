#include "handlers/RoomAdminRequestHandler.h"

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& requestInfo) const
{
	for (auto& user : m_room.getAllUsers())
	{
		if (user == m_user.getUsername())
			continue;
		Communicator::instance().usernameToSocket[user]->send(
			JsonRequestPacketSerializer::serializeResponse(LeaveRoomResponse{ LeaveRoomResponse::SUCCESS })
		);
	}

	RoomManager::instance().deleteRoom(m_room.getRoomData().id);

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(CloseRoomResponse{CloseRoomResponse::SUCCESS}),
		(IRequestHandler*)RequestHandlerFactory::instance().createMenuRequestHandler(m_user)
	};
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& requestInfo) const
{
	for (auto& user : m_room.getAllUsers())
	{
		if (user == m_user.getUsername())
			continue;
		Communicator::instance().usernameToSocket[user]->send(
			JsonRequestPacketSerializer::serializeResponse(StartGameResponse{ StartGameResponse::SUCCESS })
		);
	}

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(StartGameResponse{StartGameResponse::SUCCESS}),
		(IRequestHandler*)this // game handler
	};
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
	case IDS::CloseRoomRequest: case IDS::StartGameRequest: case IDS::GetRoomStateRequest:
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

	case IDS::GetRoomStateRequest:
		return getRoomState(requestInfo);
	}
}

/// <summary>
/// Create a new RoomAdmin Handler
/// </summary>
RoomAdminRequestHandler::RoomAdminRequestHandler(const Room& room, const LoggedUser& user) :
	IRoomMemberRequestHandler(room, user)
{
}
