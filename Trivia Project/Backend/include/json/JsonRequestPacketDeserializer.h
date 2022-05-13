#pragma once
#include "json/json.hpp"
#include <vector>
#include <string>
#include "requests/LoginRequest.h"
#include "requests/SignupRequest.h"
#include "utils/Singleton.h"

using namespace nlohmann;

class JsonRequestPacketDeserializer
{
	MAKE_SINGLETON(JsonRequestPacketDeserializer);
	JsonRequestPacketDeserializer() = default;
	~JsonRequestPacketDeserializer() = default;

public:
	static LoginRequest deserializeLoginRequest(const std::string& buffer);
	static SignupRequest deserializeSignupRequest(const std::string& buffer);
};
