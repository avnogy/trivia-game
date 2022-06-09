#pragma once
#include "handlers/IRoomMemberRequestHandler.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "infrastructure/Communicator.h"

class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRoomMemberRequestHandler
{
private:
	RequestResult closeRoom(const RequestInfo& requestInfo) const;
	RequestResult startGame(const RequestInfo& requestInfo) const;

public:
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;

	RoomAdminRequestHandler(Room& room, const LoggedUser& user);
};
