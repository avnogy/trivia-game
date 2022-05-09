#pragma once

#include <vector>
#include "database/IDatabase.h"
#include "managers/LoggedUser.h"
#include "database/SqliteDataBase.h"

class LoginManager
{
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;

public:
	void signup(const std::string& username, const std::string& password, const std::string& email);
	void login(const std::string& username, const std::string& password);
	void logout(const std::string& username);
};