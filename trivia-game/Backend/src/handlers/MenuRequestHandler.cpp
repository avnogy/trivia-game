#include "handlers/MenuRequestHandler.h"

/// <summary>
/// logout a user
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::logout(const RequestInfo& requestInfo) const
{
	bool result = LoginManager::instance().logout(m_user.getUsername());

	ReturnNewRequestResult(
		SERIALIZE(LogoutResponse{ (unsigned int)(result == true ? LogoutResponse::SUCCESS : LogoutResponse::FAILURE) }),
		RequestHandlerFactory::instance().createLoginRequestHandler()
	);
}

/// <summary>
/// get all rooms
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo) const
{
	auto result = RoomManager::instance().getRooms();

	return RequestResult{
		SERIALIZE((GetRoomsResponse{ GetRoomsResponse::SUCCESS, result })),
		(IRequestHandler*)this
	};
}

/// <summary>
/// get all players in a room
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo) const
{
	GetPlayersInRoomRequest request = DESERIALIZE(GetPlayersInRoomRequest, requestInfo.buffer);
	auto result = RoomManager::instance().getPlayersInRoom(request.roomId);

	return RequestResult{
		SERIALIZE(GetPlayersInRoomResponse{ result }),
		(IRequestHandler*)this
	};
}

/// <summary>
/// get user statistics
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo) const
{
	auto result = StatisticsManager::instance().getUserStatistics(m_user.getUsername());

	return RequestResult{
		SERIALIZE((GetStatisticsResponse{ GetStatisticsResponse::SUCCESS, result })),
		(IRequestHandler*)this
	};
}

/// <summary>
/// get top 5 most successful players
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo) const
{
	auto result = StatisticsManager::instance().getHighScore();

	return RequestResult{
		SERIALIZE((GetHighScoreResponse{ GetHighScoreResponse::SUCCESS, result })),
		(IRequestHandler*)this
	};
}

/// <summary>
/// Join user to an existing room
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo) const
{
	JoinRoomRequest request = DESERIALIZE(JoinRoomRequest, requestInfo.buffer);
	bool result = ((RoomManager::instance().getPlayersInRoom(request.roomId).size() < RoomManager::instance().getRooms()[request.roomId].maxPlayers) &&
		RoomManager::instance().joinRoom(m_user, request.roomId));
	switch (result)
	{
	case true:
		ReturnNewRequestResult(
			SERIALIZE(JoinRoomResponse{ JoinRoomResponse::SUCCESS }),
			RequestHandlerFactory::instance().createRoomMemberRequestHandler(RoomManager::instance().getRoom(request.roomId), m_user)
		);

	case false:
		return {
			SERIALIZE(JoinRoomResponse{JoinRoomResponse::FAILURE}),
			(IRequestHandler*)this
		};
	}
}

/// <summary>
/// Creating a new room for other player to join into.
/// </summary>
/// <param name="requestInfo">information about the request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo) const
{
	CreateRoomRequest request = DESERIALIZE(CreateRoomRequest, requestInfo.buffer);
	RoomData roomData = { RoomManager::instance().getNextRoomId(), request.roomName, request.maxUsers, request.questionCount, request.answerTimeout, true };
	bool result = RoomManager::instance().createRoom(m_user, roomData);

	switch (result)
	{
	case true:
		ReturnNewRequestResult(
			SERIALIZE(CreateRoomResponse{ CreateRoomResponse::SUCCESS }),
			RequestHandlerFactory::instance().createRoomAdminRequestHandler(RoomManager::instance().getRoom(roomData.id), m_user)
		);

	case false:
		return {
			SERIALIZE(CreateRoomResponse{CreateRoomResponse::FAILURE}),
			(IRequestHandler*)this
		};
	}
}

/// <summary>
/// adds a question to the database
/// </summary>
/// <param name="requestInfo"></param>
/// <returns></returns>
RequestResult MenuRequestHandler::addQuestion(const RequestInfo& requestInfo) const
{
	createLockFile(); //creating a file that says that the questions are custom and should not be overridden unting the next game
	AddQuestionRequest request = DESERIALIZE(AddQuestionRequest, requestInfo.buffer);
	//putting correct answer at [0]
	request.possibleAnswers.insert(request.possibleAnswers.begin(), request.correctAnswer);
	Question question{ request.question,request.possibleAnswers };
	bool result = IDatabase::instance()->addQuestion(question);

	return RequestResult{
	SERIALIZE(LogoutResponse{ (unsigned int)(result == true ? LogoutResponse::SUCCESS : LogoutResponse::FAILURE) }),
	(IRequestHandler*)this
	};
}

/// <summary>
/// Creating an new MenuRequestHandler
/// </summary>
/// <param name="user">user to give the handler to</param>
MenuRequestHandler::MenuRequestHandler(const LoggedUser& user) :
	m_user(user)
{
}

/// <summary>
/// Checks if the request is relevant to the MenuRequestHandler
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>whether request is relevant to MenuRequestHandler</returns>
bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (requestInfo.id)
	{
	case IDS::CreateRoomRequest:
	case IDS::GetRoomsRequest:
	case IDS::GetPlayersInRoomRequest:
	case IDS::JoinRoomRequest:
	case IDS::GetStatisticsRequest:
	case IDS::LogoutRequest:
	case IDS::GetLeaderboardRequest:
	case IDS::AddQuestionRequest:
		return true;
	default:
		return false;
	}
}

/// <summary>
/// Calling right function to handle request
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>whether request succeeded and next handler</returns>
RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (requestInfo.id)
	{
	case IDS::CreateRoomRequest:
		return createRoom(requestInfo);

	case IDS::GetRoomsRequest:
		return getRooms(requestInfo);

	case IDS::GetPlayersInRoomRequest:
		return getPlayersInRoom(requestInfo);

	case IDS::JoinRoomRequest:
		return joinRoom(requestInfo);

	case IDS::GetStatisticsRequest:
		return getPersonalStats(requestInfo);

	case IDS::GetLeaderboardRequest:
		return getHighScore(requestInfo);

	case IDS::LogoutRequest:
		return logout(requestInfo);

	case IDS::AddQuestionRequest:
		return addQuestion(requestInfo);
	}
}