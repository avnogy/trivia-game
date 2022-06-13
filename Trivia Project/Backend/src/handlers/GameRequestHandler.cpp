#include "handlers/GameRequestHandler.h"

/// <summary>
/// Getting the question for a user
/// </summary>
/// <param name="requestInfo">inforamtion about request</param>
RequestResult GameRequestHandler::getQuestion(const RequestInfo& requestInfo) const
{
	if (m_game->getQuestions().size() > 0)
	{
		return RequestResult{
			JsonRequestPacketSerializer::instance().serializeResponse(
				GetQuestionResponse{GetQuestionResponse::SUCCESS, m_game->getQuestion()}
			),
			(IRequestHandler*)this
		};
	}
	else
	{
		return RequestResult{
			JsonRequestPacketSerializer::instance().serializeResponse(
				GetGameResultsResponse{GetGameResultsResponse::SUCCESS, m_game->getGameResults()}
			),
			(IRequestHandler*)this
		};
	}
}

/// <summary>
/// submitting an answer
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult GameRequestHandler::submitAnswer(const RequestInfo& requestInfo) 
{
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::instance().deserializeSubmitAnswerRequest(requestInfo.buffer);
	m_game->submitAnswer(m_user, request.answer);

	return RequestResult{
		JsonRequestPacketSerializer::instance().serializeResponse(
			SubmitAnswerResponse{SubmitAnswerResponse::SUCCESS}
		),
		this
	};
}

/// <summary>
/// Getting the game results of all players in game
/// </summary>
/// <param name="requestInfo">information about request</param>
RequestResult GameRequestHandler::getGameResults(const RequestInfo& requestInfo) const
{
	return RequestResult{
		JsonRequestPacketSerializer::instance().serializeResponse(
			GetGameResultsResponse{GetGameResultsResponse::SUCCESS, m_game->getGameResults()}
		),
		(IRequestHandler*)this
	};
}

/// <summary>
/// removing a player from the game
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns></returns>
RequestResult GameRequestHandler::leaveGame(const RequestInfo& requestInfo)
{
	m_game->removePlayer(m_user);
	return RequestResult{
		JsonRequestPacketSerializer::instance().serializeResponse(LeaveGameResponse{LeaveGameResponse::SUCCESS}),
		this
	};
}

/// <summary>
/// Create a new GameRequestHandler
/// </summary>
/// <param name="game">game</param>
/// <param name="user">user</param>
GameRequestHandler::GameRequestHandler(Game* game, const LoggedUser& user) :
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
	case IDS::LeaveGameRequest: case IDS::GetQuestionRequest: case IDS::SubmitAnswerRequest: case IDS::GetGameResultRequest:
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
		
	case IDS::GetGameResultRequest:
		return getGameResults(requestInfo);
	}
}
