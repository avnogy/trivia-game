#pragma once
#include "handlers/IRoomMemberRequestHandler.h"

class RoomAdminRequestHandler : public IRoomMemberRequestHandler
{
private:
	RequestResult closeRoom(const RequestInfo& requestInfo) const;
	RequestResult startGame(const RequestInfo& requestInfo) const;

public:
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
