#pragma once
#include "json.hpp"
#include <vector>

#include "LoginRequest.h"
#include "SignupRequest.h"

using Byte = unsigned char;
using Buffer = std::vector<Byte>;

class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer() = default;
	~JsonRequestPacketDeserializer() = default;

	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignupRequest deserializeSignupRequest(Buffer buffer);
};
