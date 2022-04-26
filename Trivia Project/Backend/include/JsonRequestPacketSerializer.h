#pragma once
#include "json.hpp"
#include <vector>

#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"

using Byte = unsigned char;
using Buffer = std::vector<Byte>;

class JsonRequestPacketSerializer
{
public:
	JsonRequestPacketSerializer() = default;
	~JsonRequestPacketSerializer() = default;

	static Buffer serializeResponse(ErrorResponse response);
	static Buffer serializeResponse(LoginResponse response);
	static Buffer serializeResponse(SignupResponse response);
};