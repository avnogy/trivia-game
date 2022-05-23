#include "infrastructure/json/JsonRequestPacketSerializer.h"

/// <summary>
/// serialize error response
/// </summary>
/// <param name="response">error response</param>
/// <returns>serialized response</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const ErrorResponse& response)
{
	nlohmann::json json;
	json["message"] = response.message;
	return json.dump();
}

/// <summary>
/// serialize login response
/// </summary>
/// <param name="response">login response</param>
/// <returns>serialized response</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const LoginResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize signup response
/// </summary>
/// <param name="response">signup response</param>
/// <returns>serialized response</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const SignupResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize logout response
/// </summary>
/// <param name="response">logout response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const LogoutResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize get room response
/// </summary>
/// <param name="response">get room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["rooms"] = response.rooms;
	return json.dump();
}

/// <summary>
/// serialize get players in room response
/// </summary>
/// <param name="response">get players in room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
	nlohmann::json json;
	json["players"] = response.players;
	return json.dump();
}

/// <summary>
/// serialize join room response
/// </summary>
/// <param name="response">join room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize create room response
/// </summary>
/// <param name="response">create room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize statistics response
/// </summary>
/// <param name="response">statistics response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const StatisticsResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["statistics"] = response.statistics;
	return json.dump();
}

/// <summary>
/// serialize high score response
/// </summary>
/// <param name="response">get high score response</param>
/// <returns>buffer</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["highScore"] = response.highScore;
	return json.dump();
}