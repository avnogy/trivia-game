#pragma once
#include "requests/RequestInfo.h"
#include "requests/RequestResult.h"

#include <iostream>
#include "infrastructure/json/JsonRequestPacketDeserializer.h"
#include "infrastructure/json/JsonRequestPacketSerializer.h"

class RequestResult;

class IRequestHandler
{
protected:
	struct IDS {
		enum {
			LoginRequest,
			SignupRequest,
			CreateRoomRequest,
			GetRoomsRequest,
			GetPlayersInRoomRequest,
			JoinRoomRequest,
			GetStatisticsRequest,
			LogoutRequest,
			CloseRoomRequest,
			StartGameRequest,
			GetRoomStateRequest,
			LeaveRoomRequest
		};
	};

public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};
