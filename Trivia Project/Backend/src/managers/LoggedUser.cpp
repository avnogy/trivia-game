#include "managers/LoggedUser.h"

/// <summary>
/// Instantiate a new Logged User
/// </summary>
/// <param name="username">username of the new user</param>
LoggedUser::LoggedUser(const std::string& username) :
	m_username(username)
{
}

/// <summary>
/// Getter for m_username
/// </summary>
/// <returns>m_username</returns>
std::string LoggedUser::getUsername() const
{
	return m_username;
}