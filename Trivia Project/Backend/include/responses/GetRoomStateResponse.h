#pragma once
#include <vector>
#include <string>

struct GetRoomStateResponse
{
	enum
	{
		SUCCESS
	};
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};