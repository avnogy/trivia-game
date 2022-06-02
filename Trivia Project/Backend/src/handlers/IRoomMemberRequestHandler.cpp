#include "handlers/IRoomMemberRequestHandler.h"

/// <summary>
/// Getting information about room:
/// state, users, num of questions, question timeout
/// </summary>
/// <param name="requestInfo">info about request</param>
/// <returns>information about room</returns>
RequestResult IRoomMemberRequestHandler::getRoomState(const RequestInfo& requestInfo) const
{
	const auto& roomData = m_room.getRoomData();

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(
			GetRoomStateResponse{ GetRoomStateResponse::SUCCESS, roomData.isActive, m_room.getAllUsers(), roomData.numOfQuestionsInGame, roomData.timePerQuestion }
		),
		(IRequestHandler*)this
	};
}