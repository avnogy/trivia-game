#pragma once
#include "json.hpp"
#include <vector>
#include <string>
#include "LoginRequest.h"
#include "SignupRequest.h"

using namespace nlohmann;

class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer() = default;
	~JsonRequestPacketDeserializer() = default;

	static LoginRequest deserializeLoginRequest(const std::string& buffer);
	static SignupRequest deserializeSignupRequest(const std::string& buffer);
};
