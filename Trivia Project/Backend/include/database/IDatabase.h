#pragma once
#include <string>
#include <vector>
#include "database/Question.h"

#define DATABASE_FILE_PATH "D:/Coding/magshimim/Advanced-Programming/trivia-project/Trivia Project/database.sqlite"

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

	//questions
	virtual std::vector<Question> getQuestions() const = 0;
};
