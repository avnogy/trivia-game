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
/// deserialize a buffer (message from client)
/// </summary>
/// <param name="buffer">
/// 		The message is json content
/// </param>
/// <returns></returns>
SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const std::string& buffer)
{
	json bufferContent = json::parse(buffer);

	return SubmitAnswerRequest{
		bufferContent["answerId"]
	};
}
