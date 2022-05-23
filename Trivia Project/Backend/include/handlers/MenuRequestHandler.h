#pragma once
#include "handlers/IRequestHandler.h"
#include "managers/LoggedUser.h"
#include "requests/RequestResult.h"
#include "requests/RequestInfo.h"
#include "managers/RoomManager/RoomManager.h"
#include "managers/LoginManager/LoginManager.h"
#include "managers/StatisticsManager/StatisticsManager.h"

#include "requests/CreateRoomRequest.h"
#include "requests/GetPlayersInRoomRequest.h"
#include "requests/JoinRoomRequest.h"
#include "requests/GetRoomsRequest.h"
#include "requests/GetStatisticsRequest.h"
#include "requests/GetHighScoreRequest.h"

#include "responses/GetHighScoreResponse.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	const LoggedUser m_user;

	RequestResult logout(const RequestInfo& requestInfo);
	RequestResult getRooms(const RequestInfo& requestInfo);
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo);
	RequestResult getPersonalStats(const RequestInfo& requestInfo);
	RequestResult getHighScore(const RequestInfo& requestInfo);
	RequestResult joinRoom(const RequestInfo& requestInfo);
	RequestResult createRoom(const RequestInfo& requestInfo);

public:
	MenuRequestHandler(const LoggedUser& user);

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
