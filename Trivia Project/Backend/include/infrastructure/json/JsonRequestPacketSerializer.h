#pragma once
#include "infrastructure/json/json.hpp"
#include <vector>
#include "responses/LoginResponse.h"
#include "responses/SignupResponse.h"
#include "responses/ErrorResponse.h"
#include "responses/LogoutResponse.h"
#include "responses/GetRoomsResponse.h"
#include "responses/GetPlayersInRoomResponse.h"
#include "responses/JoinRoomResponse.h"
#include "responses/CreateRoomResponse.h"
#include "responses/StatisticsResponse.h"
#include "responses/GetHighScoreResponse.h"
#include "utils/Singleton.h"
#include "responses/CloseRoomResponse.h"
#include "responses/StartGameResponse.h"
#include "responses/GetRoomStateResponse.h"
#include "responses/LeaveRoomResponse.h"

class JsonRequestPacketSerializer
{
	MAKE_SINGLETON(JsonRequestPacketSerializer);
	JsonRequestPacketSerializer() = default;
	~JsonRequestPacketSerializer() = default;

public:
	static std::string serializeResponse(const ErrorResponse& response);
	static std::string serializeResponse(const LoginResponse& response);
	static std::string serializeResponse(const SignupResponse& response);

	static std::string serializeResponse(const LogoutResponse& response);
	static std::string serializeResponse(const GetRoomsResponse& response);
	static std::string serializeResponse(const GetPlayersInRoomResponse& response);
	static std::string serializeResponse(const JoinRoomResponse& response);
	static std::string serializeResponse(const CreateRoomResponse& response);
	static std::string serializeResponse(const StatisticsResponse& response);
	static std::string serializeResponse(const GetHighScoreResponse& response);

	static std::string serializeResponse(const CloseRoomResponse& response);
	static std::string serializeResponse(const StartGameResponse& response);
	static std::string serializeResponse(const GetRoomStateResponse& response);
	static std::string serializeResponse(const LeaveRoomResponse& response);
};