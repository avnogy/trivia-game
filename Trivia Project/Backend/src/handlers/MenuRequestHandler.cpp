#include "handlers/MenuRequestHandler.h"

/// <summary>
/// logout a user
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::logout(const RequestInfo& requestInfo) const
{
	bool result = LoginManager::instance().logout(m_user.getUsername());

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(LogoutResponse{ (unsigned int)(result == true ? LogoutResponse::SUCCESS : LogoutResponse::FAILURE) }),
		RequestHandlerFactory::instance().createLoginRequestHandler()
	}; 
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
		JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse{ GetRoomsResponse::SUCCESS, result }),
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
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);
	auto result = RoomManager::instance().getPlayersInRoom(request.roomId);

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse{ result }),
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
		JsonRequestPacketSerializer::serializeResponse(GetStatisticsResponse{ GetStatisticsResponse::SUCCESS, result }),
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
		JsonRequestPacketSerializer::serializeResponse(GetHighScoreResponse{ GetHighScoreResponse::SUCCESS, result }),
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
	JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	bool result = RoomManager::instance().joinRoom(m_user, request.roomId);

	switch (result)
	{
	case true:
		return {
			JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse{JoinRoomResponse::SUCCESS}),
			RequestHandlerFactory::instance().createRoomMemberRequestHandler(RoomManager::instance().getRoom(request.roomId), m_user)
		};

	case false:
		return {
			JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse{JoinRoomResponse::FAILURE}),
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
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
	RoomData roomData = { RoomManager::instance().getNextRoomId(), request.roomName, request.maxUsers, request.questionCount, request.answerTimeout, true };
	bool result = RoomManager::instance().createRoom(m_user, roomData);

	switch (result)
	{
	case true:
		return {
			JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{CreateRoomResponse::SUCCESS}),
			RequestHandlerFactory::instance().createRoomAdminRequestHandler(RoomManager::instance().getRoom(RoomManager::instance().getNextRoomId()), m_user)
		}; 

	case false:
		return {
			JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{CreateRoomResponse::FAILURE}),
			(IRequestHandler*)this
		};
	}
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
	case IDS::CreateRoomRequest: case IDS::GetRoomsRequest: case IDS::GetPlayersInRoomRequest: case IDS::JoinRoomRequest: case IDS::GetStatisticsRequest: case IDS::LogoutRequest:
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

	case IDS::LogoutRequest:
		return logout(requestInfo);
	}
}