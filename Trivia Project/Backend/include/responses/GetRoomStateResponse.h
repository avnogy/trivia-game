#pragma once
#include <vector>
#include <string>

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegub;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};