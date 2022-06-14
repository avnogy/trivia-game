#pragma once
#include <string>
#include <vector>
#include "infrastructure/json/json.hpp"

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	float averageAnswerTime;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(PlayerResults, username, correctAnswerCount, wrongAnswerCount, averageAnswerTime);
};

struct GetGameResultsResponse
{
	enum
	{
		SUCCESS
	};
	unsigned int status;
	std::vector<PlayerResults> results;
};
