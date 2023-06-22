#pragma once
#include <vector>
#include <string>

struct GetStatisticsResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
	std::vector<std::string> statistics;
};