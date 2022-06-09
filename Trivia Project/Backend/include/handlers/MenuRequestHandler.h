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

#include "responses/GetHighScoreResponse.h"

#include "infrastructure/RequestHandlerFactory.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
private:
	const LoggedUser m_user;

	RequestResult logout(const RequestInfo& requestInfo) const;
	RequestResult getRooms(const RequestInfo& requestInfo) const;
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo) const;
	RequestResult getPersonalStats(const RequestInfo& requestInfo) const;
	RequestResult getHighScore(const RequestInfo& requestInfo) const;
	RequestResult joinRoom(const RequestInfo& requestInfo) const;
	RequestResult createRoom(const RequestInfo& requestInfo) const;

public:
	MenuRequestHandler(const LoggedUser& user);

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
