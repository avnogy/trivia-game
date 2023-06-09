#pragma once
#include "handlers/IRoomMemberRequestHandler.h"
#include "infrastructure/RequestHandlerFactory.h"
#include "infrastructure/Communicator.h"

class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRoomMemberRequestHandler
{
private:
	RequestResult leaveRoom(const RequestInfo& requestInfo);
	RequestResult logout(const RequestInfo& requestInfo);

public:
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;

	RoomMemberRequestHandler(Room& room, const LoggedUser& user);
};
