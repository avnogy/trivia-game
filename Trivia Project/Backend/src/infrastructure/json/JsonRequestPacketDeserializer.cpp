#include "infrastructure/json/JsonRequestPacketDeserializer.h"

/// <summary>
/// deserialize a buffer (message from client)
/// </summary>
/// <param name="buffer">
///		buffer looks like this: <status><message size><message>
///		The message is json content
/// </param>
/// <returns>Login Request containing the json content</returns>
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return LoginRequest{
		bufferContent["username"],
		bufferContent["password"]
	};
}

/// <summary>
/// deserialize a buffer (message from client)
/// </summary>
/// <param name="buffer">
///		buffer looks like this: <status><message size><message>
///		The message is json content
/// </param>
/// <returns>Signup Request containing the json content</returns>
SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return SignupRequest{
		bufferContent["username"],
		bufferContent["password"],
		bufferContent["email"]
	};
}

/// <summary>
/// deserialize a buffer (message from client)
/// </summary>
/// <param name="buffer">
/// 		The message is json content
/// </param>
/// <returns></returns>
GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return GetPlayersInRoomRequest{
		bufferContent["roomId"]
	};
}

/// <summary>
/// deserialize a buffer (message from client)
/// </summary>
/// <param name="buffer">
/// 		The message is json content
/// </param>
/// <returns></returns>
JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return JoinRoomRequest{
		bufferContent["roomId"]
	};
}

/// <summary>
/// deserialize a buffer (message from client)
/// </summary>
/// <param name="buffer">
/// 		The message is json content
/// </param>
/// <returns></returns>
CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return CreateRoomRequest{
		bufferContent["roomName"],
		bufferContent["maxUsers"],
		bufferContent["questionCount"],
		bufferContent["answerTimeout"]
	};
}

/// <summary>
/// Deserializing a Logout request buffer
/// </summary>
/// <param name="buffer">buffer</param>
/// <returns>Logout Request class</returns>
LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return LogoutRequest{
		bufferContent["username"]
	};
}

/// <summary>
/// Deserializing a get statistics request buffer
/// </summary>
/// <param name="buffer">buffer</param>
/// <returns>get statistics Request class</returns>
GetStatisticsRequest JsonRequestPacketDeserializer::deserializeGetStatisticsRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return GetStatisticsRequest{
		bufferContent["username"]
	};
}

/// <summary>
/// Deserializing a get rooms request buffer
/// </summary>
/// <param name="buffer">buffer</param>
/// <returns>get rooms Request class</returns>
GetRoomsRequest JsonRequestPacketDeserializer::deserializeGetRoomsRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return GetRoomsRequest{
	};
}

/// <summary>
/// Deserializing a get high score request buffer
/// </summary>
/// <param name="buffer">buffer</param>
/// <returns>get high score Request class</returns>
GetHighScoreRequest JsonRequestPacketDeserializer::deserializeGetHighScoreRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return GetHighScoreRequest{
	};
}