#pragma once
#include "handlers/IRoomMemberRequestHandler.h"

class RoomMemberRequestHandler : public IRoomMemberRequestHandler
{
private:
	RequestResult leaveRoom(const RequestInfo& requestInfo);

public:
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
