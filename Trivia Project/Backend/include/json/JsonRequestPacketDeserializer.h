#pragma once
#include "json/json.hpp"
#include <vector>
#include <string>
#include "requests/LoginRequest.h"
#include "requests/SignupRequest.h"

using namespace nlohmann;

class JsonRequestPacketDeserializer
{
public:
	JsonRequestPacketDeserializer() = default;
	~JsonRequestPacketDeserializer() = default;

	static LoginRequest deserializeLoginRequest(const std::string& buffer);
	static SignupRequest deserializeSignupRequest(const std::string& buffer);
};
