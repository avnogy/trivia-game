#pragma once
#include "json.hpp"
#include <vector>
#include <string>
#include "Buffer.h"
#include "LoginRequest.h"
#include "SignupRequest.h"

using namespace nlohmann;

class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer() = default;
	~JsonRequestPacketDeserializer() = default;

	static LoginRequest deserializeLoginRequest(const Buffer& buffer);
	static SignupRequest deserializeSignupRequest(const Buffer& buffer);
};
