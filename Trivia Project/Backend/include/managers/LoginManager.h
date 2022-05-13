#pragma once

#include <unordered_set> //hash table - constant search, diables duplicates.
#include "database/IDatabase.h"
#include "managers/LoggedUser.h"
#include "database/SqliteDataBase.h"
#include "requests/RequestResult.h"
#include "database/DatabaseError.h"
#include "utils/Singleton.h"

class LoginManager
{
	MAKE_SINGLETON(LoginManager);
	DELETE_CONSTRUCTOR(LoginManager);

private:
	std::unordered_set<LoggedUser> m_loggedUsers;

public:
	LoginManager(IDatabase* database);

	bool signup(const std::string& username, const std::string& password, const std::string& email);
	bool login(const std::string& username, const std::string& password);
	bool logout(const std::string& username);
};