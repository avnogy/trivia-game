#pragma once

#include "infrastructure/database/IDatabase.h"
#include "managers/LoggedUser.h"
#include "infrastructure/database/SqliteDataBase.h"
#include "infrastructure/Communicator.h"
#include "requests/RequestResult.h"
#include "infrastructure/database/DatabaseError.h"

class LoginManager
{
	MAKE_SINGLETON(LoginManager);
	DELETE_CONSTRUCTOR(LoginManager);

private:
	std::unordered_set<LoggedUser> m_loggedUsers;

public:
	bool signup(const std::string& username, const std::string& password, const std::string& email);
	bool login(const std::string& username, const std::string& password);
	bool logout(const std::string& username);
};