#include "handlers/GameRequestHandler.h"

/// <summary>
/// Getting the question for a user
/// </summary>
/// <param name="requestInfo">inforamtion about request</param>
RequestResult GameRequestHandler::getQuestion(const RequestInfo& requestInfo) const
{
	return RequestResult{
		SERIALIZE((GetQuestionResponse{ GetQuestionResponse::SUCCESS, m_game->getQuestion() })),
		(IRequestHandler*)this
	};
}

/// <summary>
/// submitting an answer
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo) 
{
	SubmitAnswerRequest request = DESERIALIZE(SubmitAnswerRequest, requestInfo.buffer);

	if (m_game->isAlreadySubmited(m_user))
	{
		return RequestResult{
			SERIALIZE(SubmitAnswerResponse{SubmitAnswerResponse::FAILURE}),
			this
		};
	}
	else
	{
		m_game->submitAnswer(m_user, request.answer, request.timeToAnswer);

		return RequestResult{
			SERIALIZE(SubmitAnswerResponse{SubmitAnswerResponse::SUCCESS}),
			this
		};
	}
}

/// <summary>
/// removing a player from the game
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns></returns>
RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo)
{
	m_game->removePlayer(m_user);
	ReturnNewRequestResult(
		SERIALIZE(LeaveGameResponse{LeaveGameResponse::SUCCESS}),
		RequestHandlerFactory::instance().createMenuRequestHandler(m_user)
	);
}


/// <summary>
/// logs out the user in the middle of a game
/// </summary>
/// <param name="requestInfo"></param>
/// <returns></returns>
RequestResult GameRequestHandler::logout(const RequestInfo& requestInfo)
{
	leaveGame(requestInfo);
	bool result = LoginManager::instance().logout(m_user.getUsername());
	ReturnNewRequestResult(
		SERIALIZE((LogoutResponse{ (unsigned int)(result == true ? LogoutResponse::SUCCESS : LogoutResponse::FAILURE) })),
		RequestHandlerFactory::instance().createLoginRequestHandler()
	);
}

/// <summary>
/// Create a new GameRequestHandler
/// </summary>
/// <param name="game">game</param>
/// <param name="user">user</param>
GameRequestHandler::GameRequestHandler(std::shared_ptr<Game> game, const LoggedUser& user) :
	m_game(game), m_user(user)
{
}

/// <summary>
/// Checks whether request is relevant to handler
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>whether request is relevent</returns>
bool GameRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (requestInfo.id)
	{
	case IDS::LeaveGameRequest: 
	case IDS::GetQuestionRequest: 
	case IDS::SubmitAnswerRequest: 	
	case IDS::LogoutRequest:
		return true;
	default:
		return false;
	}
}

/// <summary>
/// handling request. calling right function for the request
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult GameRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (requestInfo.id)
	{
	case IDS::LeaveGameRequest:
		return leaveGame(requestInfo);

	case IDS::GetQuestionRequest:
		return getQuestion(requestInfo);

	case IDS::SubmitAnswerRequest:
		return submitAnswer(requestInfo);

	case IDS::LogoutRequest:
		return logout(requestInfo);
	}
}
