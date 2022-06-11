#include "managers/LoginManager/LoginManager.h"

/// <summary>
/// Adding a new user to database
/// </summary>
/// <param name="username">username of user</param>
/// <param name="password">password of user</param>
/// <param name="email">email of user</param>
/// <returns>whether the signup succeeded or not</returns>
bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
	//if user is already signed up
	if (IDatabase::instance()->doesUserExist(username))
		return false;

	IDatabase::instance()->addNewUser(username, password, email);
	return true;
}

/// <summary>
/// Logging in a user thats already in database
/// </summary>
/// <param name="username">user's username</param>
/// <param name="password">user's password</param>
/// <returns>whether the login succeeded or not</returns>
bool LoginManager::login(const std::string& username, const std::string& password)
{
	//if the user already logged in
	if (m_loggedUsers.find(username) != m_loggedUsers.end())
		return false;

	//if user not signed up or password's not match
	if ((IDatabase::instance()->doesUserExist(username) && IDatabase::instance()->doesPasswordMatch(username, password)))
	{
		m_loggedUsers.insert(username);
		return true;
	}

	return false;
}

/// <summary>
/// Logging out a user
/// </summary>
/// <param name="username">user's username</param>
/// <returns>whether the logout succeeded or not</returns>
bool LoginManager::logout(const std::string& username)
{
	//if the user is already logged out
	if (m_loggedUsers.find(username) == m_loggedUsers.end())
		return false;

	m_loggedUsers.erase(username);
	return true;
}