#pragma once
#include "infrastructure/database/DatabaseError.h"
#include "infrastructure/database/IDatabase.h"
#include "sqlite3.h"
#include <string>
#include <iostream>
#include <io.h>
#include <cassert>

#define ACCESS_CODE 6

#define SQLITE_DATABASE_ERROR DatabaseError(__FUNCTION__" - Sql request failed.")

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase(const std::string& databasePath);
	~SqliteDataBase();

	//login/logout/signup
	bool doesUserExist(const std::string& username) const override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) const override;
	void addNewUser(const std::string& username, const std::string& password, const std::string& email) const override;

	//statistics
	float getPlayerAverageAnswerTime(const std::string& username) const override;
	int getNumOfCorrectAnswers(const std::string& username) const override;
	int getNumOfTotalAnswers(const std::string& username) const override;
	int getNumOfPlayerGames(const std::string& username) const override;
	std::vector<std::string> getLeaderboard() const override;
	//questions
	std::queue<Question> getQuestions() const override;

private:
	bool sqlexec(const std::string& msg, int(*callback)(void* data, int argc, char** argv, char** azColName) = nullptr, void* callbackArg = nullptr) const;

	sqlite3* m_db;
	const std::string m_filePath;
};