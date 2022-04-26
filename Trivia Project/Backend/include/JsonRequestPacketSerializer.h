#pragma once
#include "json.hpp"
#include <vector>
#include "Buffer.h"
#include "LoginResponse.h"
#include "SignupResponse.h"
#include "ErrorResponse.h"

class JsonRequestPacketSerializer
{
public:

	JsonRequestPacketSerializer() = default;
	~JsonRequestPacketSerializer() = default;

	static Buffer serializeResponse(ErrorResponse response);
	static Buffer serializeResponse(LoginResponse response);
	static Buffer serializeResponse(SignupResponse response);
};