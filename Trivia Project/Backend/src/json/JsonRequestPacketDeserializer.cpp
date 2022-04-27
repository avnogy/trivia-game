#include "json/JsonRequestPacketDeserializer.h"

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