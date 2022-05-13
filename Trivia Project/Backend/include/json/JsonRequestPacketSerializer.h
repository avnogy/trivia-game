#pragma once
#include "json/json.hpp"
#include <vector>
#include "responses/LoginResponse.h"
#include "responses/SignupResponse.h"
#include "responses/ErrorResponse.h"
#include "utils/Singleton.h"

class JsonRequestPacketSerializer
{
	MAKE_SINGLETON(JsonRequestPacketSerializer);
	JsonRequestPacketSerializer() = default;
	~JsonRequestPacketSerializer() = default;

public:
	static std::string serializeResponse(const ErrorResponse& response);
	static std::string serializeResponse(const LoginResponse& response);
	static std::string serializeResponse(const SignupResponse& response);
};