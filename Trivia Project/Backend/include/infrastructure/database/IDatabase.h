#pragma once
#include <string>
#include <vector>
#include <queue>
#include "managers/GameManager/Question.h"

#define DATABASE_FILE_PATH "../../database.sqlite"

class IDatabase
{
private:
	static IDatabase* m_instance;

public:
	static IDatabase* instance();

	//login/logout/signup
	virtual bool doesUserExist(const std::string& username) const = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) const = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) const = 0;

	//statistics
	virtual float getPlayerAverageAnswerTime(const std::string& username) const = 0;
	virtual int getNumOfCorrectAnswers(const std::string& username) const = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) const = 0;
	virtual int getNumOfPlayerGames(const std::string& username) const = 0;
	virtual std::vector<std::string> getLeaderboard() const = 0;

	//questions
	virtual std::queue<Question> getQuestions() const = 0;
	virtual bool addQuestion(const Question& question) const = 0;
};
