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

/// <summary>
/// Used to hash the class into the unordered_set
/// </summary>
/// <param name="other">other class to compare this one to</param>
/// <returns>are the classes the same</returns>
bool LoggedUser::operator==(const LoggedUser& other) const
{
	return m_username == other.m_username;
}