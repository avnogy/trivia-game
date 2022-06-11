#include "infrastructure/json/JsonRequestPacketSerializer.h"

/// <summary>
/// serialize error response
/// </summary>
/// <param name="response">error response</param>
/// <returns>serialized response</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const ErrorResponse& response)
{
	nlohmann::json json;
	json["message"] = response.message;
	return json.dump();
}

/// <summary>
/// serialize login response
/// </summary>
/// <param name="response">login response</param>
/// <returns>serialized response</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const LoginResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize signup response
/// </summary>
/// <param name="response">signup response</param>
/// <returns>serialized response</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const SignupResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize logout response
/// </summary>
/// <param name="response">logout response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const LogoutResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize get room response
/// </summary>
/// <param name="response">get room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetRoomsResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["rooms"] = response.rooms;
	return json.dump();
}

/// <summary>
/// serialize get players in room response
/// </summary>
/// <param name="response">get players in room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetPlayersInRoomResponse& response)
{
	nlohmann::json json;
	json["players"] = response.players;
	return json.dump();
}

/// <summary>
/// serialize join room response
/// </summary>
/// <param name="response">join room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const JoinRoomResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize create room response
/// </summary>
/// <param name="response">create room response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const CreateRoomResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// serialize statistics response
/// </summary>
/// <param name="response">statistics response</param>
/// <returns></returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetStatisticsResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["statistics"] = response.statistics;
	return json.dump();
}

/// <summary>
/// serialize high score response
/// </summary>
/// <param name="response">get high score response</param>
/// <returns>buffer</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetHighScoreResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["highScore"] = response.highScore;
	return json.dump();
}

/// <summary>
/// Serialize CloseRoomResponse
/// </summary>
/// <param name="response">CloseRoomResponse</param>
/// <returns>json</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const CloseRoomResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// Serialize StartGameResponse
/// </summary>
/// <param name="response">StartGameResponse</param>
/// <returns>json</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const StartGameResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// Serialize GetRoomStateResponse
/// </summary>
/// <param name="response">GetRoomStateResponse</param>
/// <returns>json</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetRoomStateResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["hasGameBegun"] = response.hasGameBegun;
	json["players"] = response.players;
	json["questionCount"] = response.questionCount;
	json["answerTimeout"] = response.answerTimeout;

	return json;
}

/// <summary>
/// Serialize LeaveRoomResponse
/// </summary>
/// <param name="response">LeaveRoomResponse</param>
/// <returns>json</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const LeaveRoomResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}

/// <summary>
/// Serialize GetGameResultResponse struct
/// </summary>
/// <param name="response">response to serialize</param>
/// <returns>json like string</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetGameResultsResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["results"] = response.results;
	return json.dump();
}

/// <summary>
/// Serialize SubmitAnswerResponse struct
/// </summary>
/// <param name="response">response to serialize</param>
/// <returns>json like string</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const SubmitAnswerResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	json["correctAnswer"] = response.correctAnswer;
	return json.dump();
}

/// <summary>
/// Serialize GetQuestionResponse struct
/// </summary>
/// <param name="response">response to serialize</param>
/// <returns>json like string</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const GetQuestionResponse& response)
{
	nlohmann::json question;

	question["question"] = response.question.getQuestion();
	question["possibleAnswers"] = response.question.getPossibleAnswers();
	question["correctAnswer"] = response.question.getCorrectAnswer();

	return question.dump();
}

/// <summary>
/// Serialize LeaveGameResponse struct
/// </summary>
/// <param name="response">response to serialize</param>
/// <returns>json like string</returns>
std::string JsonRequestPacketSerializer::serializeResponse(const LeaveGameResponse& response)
{
	nlohmann::json json;
	json["status"] = response.status;
	return json.dump();
}
