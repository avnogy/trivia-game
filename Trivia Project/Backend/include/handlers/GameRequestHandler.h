#pragma once
#include "handlers/IRequestHandler.h"
#include "managers/GameManager/Game.h"
#include "managers/LoggedUser.h"
#include "managers/GameManager/GameManager.h"


class GameRequestHandler : public IRequestHandler
{
private:
	Game& m_game;
	LoggedUser m_user;

	RequestResult getQuestion(const RequestInfo& requestInfo) const;
	RequestResult submitAnswer(const RequestInfo& requestInfo) ;
	RequestResult getGameResults(const RequestInfo& requestInfo) const;
	RequestResult leaveGame(const RequestInfo& requestInfo);

public:
	GameRequestHandler(Game& game, const LoggedUser& user);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);
};

