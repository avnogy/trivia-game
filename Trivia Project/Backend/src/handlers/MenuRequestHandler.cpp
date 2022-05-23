#include "handlers/MenuRequestHandler.h"

/// <summary>
/// logout a user
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::logout(const RequestInfo& requestInfo)
{
	LogoutRequest request = JsonRequestPacketDeserializer::deserializeLogoutRequest(requestInfo.buffer);
	bool result = LoginManager::instance().logout(request.username);

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(LogoutResponse{ (unsigned int)(result == true ? LogoutResponse::SUCCESS : LogoutResponse::FAILURE) }),
		this
	}; //return game handler
}

/// <summary>
/// get all rooms
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getRooms(const RequestInfo& requestInfo)
{
	GetRoomsRequest request = JsonRequestPacketDeserializer::deserializeGetRoomsRequest(requestInfo.buffer);
	auto result = RoomManager::instance().getRooms();

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(GetRoomsResponse{ GetRoomsResponse::SUCCESS, result }),
		this
	}; //return game handler
}

/// <summary>
/// get all players in a room
/// </summary>
/// <param name="requestInfo">imformation about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo& requestInfo)
{
	GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);
	auto result = RoomManager::instance().getPlayersInRoom(request.roomId);

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(GetPlayersInRoomResponse{ result }),
		this
	}; //return game handler
}

/// <summary>
/// get user statistics
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo& requestInfo)
{
	GetStatisticsRequest request = JsonRequestPacketDeserializer::deserializeGetStatisticsRequest(requestInfo.buffer);
	auto result = StatisticsManager::instance().getUserStatistics(request.username);

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(StatisticsResponse{ StatisticsResponse::SUCCESS, result }),
		this
	}; //return game handler
}

/// <summary>
/// get top 5 most successful players
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::getHighScore(const RequestInfo& requestInfo)
{
	GetHighScoreRequest request = JsonRequestPacketDeserializer::deserializeGetHighScoreRequest(requestInfo.buffer);
	auto result = StatisticsManager::instance().getHighScore();

	return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(GetHighScoreResponse{ GetHighScoreResponse::SUCCESS, result }),
		this
	}; //return game handler
}

/// <summary>
/// Join user to an existing room
/// </summary>
/// <param name="requestInfo">information about request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::joinRoom(const RequestInfo& requestInfo)
{
	JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
	bool result = RoomManager::instance().joinRoom(m_user, request.roomId);

	switch (result)
	{
	case true:
		return {
			JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse{JoinRoomResponse::SUCCESS}),
			this
		}; //change this to game request handler

	case false:
		return {
			JsonRequestPacketSerializer::serializeResponse(JoinRoomResponse{JoinRoomResponse::FAILURE}),
			this
		};
	}
}

/// <summary>
/// Creating a new room for other player to join into.
/// </summary>
/// <param name="requestInfo">information about the request</param>
/// <returns>response and next handler</returns>
RequestResult MenuRequestHandler::createRoom(const RequestInfo& requestInfo)
{
	CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
	RoomData roomData = { RoomManager::instance().getNextRoomId(), request.roomName, request.maxUsers, request.questionCount, request.answerTimeout, true };
	bool result = RoomManager::instance().createRoom(m_user, roomData);

	switch (result)
	{
	case true:
		return {
			JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{CreateRoomResponse::SUCCESS}),
			this
		}; //change this to game request handler

	case false:
		return {
			JsonRequestPacketSerializer::serializeResponse(CreateRoomResponse{CreateRoomResponse::FAILURE}),
			this
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