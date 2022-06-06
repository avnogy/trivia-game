#pragma once

#include "managers/LoginManager/LoginManager.h"
#include "managers/RoomManager/RoomManager.h"
#include "managers/StatisticsManager/StatisticsManager.h"

#include "infrastructure/database/SqliteDataBase.h"

#include "handlers/LoginRequestHandler.h"
#include "handlers/MenuRequestHandler.h"
#include "handlers/RoomAdminRequestHandler.h"
#include "handlers/RoomMemberRequestHandler.h"
#include "utils/Singleton.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
	MAKE_SINGLETON(RequestHandlerFactory);
	DELETE_CONSTRUCTOR(RequestHandlerFactory);

public:
	LoginRequestHandler* createLoginRequestHandler() const;
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user) const;
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const Room& room, const LoggedUser& user) const;
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const Room& room, const LoggedUser& user) const;
};
