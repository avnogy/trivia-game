#pragma once
#include <string>
#include <vector>
#include "infrastructure/json/json.hpp"

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerResults, username, correctAnswerCount, wrongAnswerCount, averageAnswerTime);
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};
