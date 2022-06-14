#include "managers/StatisticsManager/StatisticsManager.h"

#include "managers/StatisticsManager/StatisticsManager.h"

/*
*** THINK OF A POINTING SYSTEM ***
*/
std::vector<std::string> StatisticsManager::getHighScore() const
{

	return IDatabase::instance()->getLeaderboard();

}

bool StatisticsManager::addUserStatistic(const PlayerResults& statistic) const
{
	return IDatabase::instance()->addUserStatistic(statistic);
}


/// <summary>
/// Getting all user statistics
/// </summary>
/// <param name="username">username of user</param>
/// <returns>average answer time, num of correct answers, num of total answers, num of games</returns>
std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
	std::vector<std::string> userStatistics;
	userStatistics.push_back(
		std::to_string(IDatabase::instance()->getPlayerAverageAnswerTime(username))
	);
	userStatistics.push_back(
		std::to_string(IDatabase::instance()->getNumOfCorrectAnswers(username))
	);
	userStatistics.push_back(
		std::to_string(IDatabase::instance()->getNumOfTotalAnswers(username))
	);
	userStatistics.push_back(
		std::to_string(IDatabase::instance()->getNumOfPlayerGames(username))
	);
	return userStatistics;
}