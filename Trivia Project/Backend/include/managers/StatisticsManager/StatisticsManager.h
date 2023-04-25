#pragma once
#include <vector>
#include <string>
#include <map>
#include "infrastructure/database/IDatabase.h"
#include "responses/GetGameResultsResponse.h"
#include "utils/Singleton.h"

class StatisticsManager
{
	MAKE_SINGLETON(StatisticsManager);
	DELETE_CONSTRUCTOR(StatisticsManager);
public:
	std::vector<std::string> getHighScore() const;
	bool addUserStatistic(const PlayerResults& statistic) const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;
};