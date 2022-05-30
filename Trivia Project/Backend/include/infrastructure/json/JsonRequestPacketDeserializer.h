#pragma once
#include "infrastructure/json/json.hpp"
#include <vector>
#include <string>
#include "requests/LoginRequest.h"
#include "requests/SignupRequest.h"
#include "requests/GetPlayersInRoomRequest.h"
#include "requests/CreateRoomRequest.h"
#include "requests/JoinRoomRequest.h"
#include "requests/GetRoomsRequest.h"
#include "requests/GetStatisticsRequest.h"
#include "requests/LogoutRequest.h"
#include "requests/GetHighScoreRequest.h"
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
	static LogoutRequest deserializeLogoutRequest(const std::string& buffer);
	static GetStatisticsRequest deserializeGetStatisticsRequest(const std::string& buffer);
	static GetRoomsRequest deserializeGetRoomsRequest(const std::string& buffer);
	static GetHighScoreRequest deserializeGetHighScoreRequest(const std::string& buffer);
};