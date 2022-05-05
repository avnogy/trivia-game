#include "json/JsonRequestPacketSerializer.h"

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