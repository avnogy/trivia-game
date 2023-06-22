#pragma once
#include <vector>
#include <string>

struct GetHighScoreResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};

	unsigned int status;
	std::vector<std::string> highScore;
};