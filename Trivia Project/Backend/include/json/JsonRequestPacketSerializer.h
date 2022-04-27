#pragma once
#include "json/json.hpp"
#include <vector>
#include "responses/LoginResponse.h"
#include "responses/SignupResponse.h"
#include "responses/ErrorResponse.h"

class JsonRequestPacketSerializer
{
public:

	JsonRequestPacketSerializer() = default;
	~JsonRequestPacketSerializer() = default;

	static std::string serializeResponse(const ErrorResponse& response);
	static std::string serializeResponse(const LoginResponse& response);
	static std::string serializeResponse(const SignupResponse& response);
};