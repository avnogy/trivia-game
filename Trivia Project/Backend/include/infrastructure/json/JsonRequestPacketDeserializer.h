#pragma once
#include "infrastructure/json/json.hpp"
#include <vector>
#include <string>
#include "requests/LoginRequest.h"
#include "requests/SignupRequest.h"
#include "requests/GetPlayersInRoomRequest.h"
#include "requests/CreateRoomRequest.h"
#include "requests/JoinRoomRequest.h"
#include "requests/SubmitAnswerRequest.h"
#include "requests/AddQuestionRequest.h"
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

	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const std::string& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const std::string& buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(const std::string& buffer);

	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const std::string& buffer);
	static AddQuestionRequest deserializeAddQuestionRequest(const std::string& buffer);
};
