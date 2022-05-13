#pragma once
#include <string>

#define DATABASE_FILE_PATH "D:/Coding/magshimim/Advanced-Programming/trivia-project/Trivia Project/database.sqlite"

class IDatabase
{
private:
	static IDatabase* m_instance;

public:
	virtual bool doesUserExist(const std::string& username) const = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) const = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) = 0;

	static IDatabase* instance();
};
