#pragma once
#include <vector>
#include <string>

struct StatisticsResponse
{
	unsigned int status;
	std::vector<std::string> statistics;
};