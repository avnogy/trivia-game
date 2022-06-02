#include "handlers/RoomMemberRequestHandler.h"

/// <summary>
/// Leaving the room
/// </summary>
/// <param name="requestInfo">information about result</param>
/// <returns>response and next handler</returns>
RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& requestInfo)
{
	bool result = m_room.removeUser(m_user);

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(LeaveRoomResponse{result ? LeaveRoomResponse::SUCCESS : LeaveRoomResponse::FAILURE}),
		(IRequestHandler*)RequestHandlerFactory::instance().createMenuRequestHandler(m_user)
	};
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
	case IDS::LeaveRoomRequest: case IDS::GetRoomStateRequest:
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
	}
}