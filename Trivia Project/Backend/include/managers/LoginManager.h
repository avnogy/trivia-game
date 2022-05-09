#pragma once

#include <unordered_set> //hash table - constant search, diables duplicates.
#include "database/IDatabase.h"
#include "managers/LoggedUser.h"
#include "database/SqliteDataBase.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::unordered_set<LoggedUser> m_loggedUsers;

public:
	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);
};