#pragma once

#include "managers/RoomManager/Room.h"
#include "managers/LoggedUser.h"
#include "requests/RequestInfo.h"
#include "responses/GetRoomStateResponse.h"
#include "infrastructure/json/JsonRequestPacketSerializer.h"
#include "handlers/IRequestHandler.h"

class IRoomMemberRequestHandler : public IRequestHandler
{
protected:
	Room m_room;
	LoggedUser m_user;

	RequestResult getRoomState(const RequestInfo& requestInfo) const;
	IRoomMemberRequestHandler(const Room& room, const LoggedUser& user);
};