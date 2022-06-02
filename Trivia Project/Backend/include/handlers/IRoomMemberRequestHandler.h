#pragma once

#include "managers/RoomManager/Room.h"
#include "managers/RoomManager/RoomManager.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "managers/LoggedUser.h"
#include "requests/RequestInfo.h"
#include "handlers/IRequestHandler.h"

class IRoomMemberRequestHandler : public IRequestHandler
{
protected:
	Room m_room;
	LoggedUser m_user;

	RequestResult getRoomState(const RequestInfo& requestInfo) const;
};