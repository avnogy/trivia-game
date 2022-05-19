#pragma once
#include <vector>
#include <string>

struct GetHighScoreResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};