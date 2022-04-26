#pragma once
#include "json.hpp"
#include <vector>
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"

class JsonRequestPacketSerializer
{
public:

	JsonRequestPacketSerializer() = default;
	~JsonRequestPacketSerializer() = default;

	static std::string serializeResponse(ErrorResponse response);
	static std::string serializeResponse(LoginResponse response);
	static std::string serializeResponse(SignupResponse response);
};