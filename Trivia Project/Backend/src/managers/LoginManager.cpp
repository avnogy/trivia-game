#include "managers/LoginManager.h"

/// <summary>
/// Adding a new user to database
/// </summary>
/// <param name="username">username of user</param>
/// <param name="password">password of user</param>
/// <param name="email">email of user</param>
void LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	m_database->addNewUser(username, password, email);
}

/// <summary>
/// Logging in a user thats already in database
/// </summary>
/// <param name="username">user's username</param>
/// <param name="password">user's password</param>
void LoginManager::login(const std::string& username, const std::string& password)
{
	//if the user already logged in, return
	if (m_loggedUsers.find(username) != m_loggedUsers.end())
		return;

	//if the user exists in database and password's match
	if (m_database->doesUserExist(username) && m_database->doesPasswordMatch(username, password))
	{
		m_loggedUsers.insert(username);
	}
}

/// <summary>
/// Logging out a user
/// </summary>
/// <param name="username">user's username</param>
void LoginManager::logout(const std::string& username)
{
	m_loggedUsers.erase(username);
}