#pragma once
#include <vector>
#include <string>
#include <map>
#include "database/IDatabase.h"

class StatisticsManager
{
public:
	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;
};