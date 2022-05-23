#pragma once
#include <vector>
#include <string>

struct StatisticsResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
	std::vector<std::string> statistics;
};