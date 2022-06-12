#pragma once
#include "infrastructure/json/json.hpp"
#include "managers/GameManager/Question.h"
#include <vector>
#include "responses/LoginResponse.h"
#include "responses/SignupResponse.h"
#include "responses/ErrorResponse.h"
#include "responses/LogoutResponse.h"
#include "responses/GetRoomsResponse.h"
#include "responses/GetPlayersInRoomResponse.h"
#include "responses/JoinRoomResponse.h"
#include "responses/CreateRoomResponse.h"
#include "responses/GetStatisticsResponse.h"
#include "responses/GetHighScoreResponse.h"
#include "utils/Singleton.h"
#include "responses/CloseRoomResponse.h"
#include "responses/StartGameResponse.h"
#include "responses/GetRoomStateResponse.h"
#include "responses/LeaveRoomResponse.h"
#include "responses/GetGameResultsResponse.h"
#include "responses/SubmitAnswerResponse.h"
#include "responses/GetQuestionResponse.h"
#include "responses/LeaveGameResponse.h"
#include "responses/UpdateResponse.h"
#include "responses/CorrectAnswerResponse.h"

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
	static std::string serializeResponse(const GetStatisticsResponse& response);
	static std::string serializeResponse(const GetHighScoreResponse& response);

	static std::string serializeResponse(const CloseRoomResponse& response);
	static std::string serializeResponse(const StartGameResponse& response);
	static std::string serializeResponse(const GetRoomStateResponse& response);
	static std::string serializeResponse(const LeaveRoomResponse& response);

	static std::string serializeResponse(const GetGameResultsResponse& response);
	static std::string serializeResponse(const SubmitAnswerResponse& response);
	static std::string serializeResponse(const GetQuestionResponse& response);
	static std::string serializeResponse(const LeaveGameResponse& response);

	static std::string serializeResponse(const UpdateResponse& response);
	static std::string serializeResponse(const CorrectAnswerResponse& response);

};