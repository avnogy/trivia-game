#include "managers/RoomManager/Room.h"

/// <summary>
/// Adding a new user to the room
/// </summary>
/// <param name="user">user to add</param>
/// <returns>whether the addition succeeded (if user already is logged in, return false)</returns>
bool Room::addUser(const LoggedUser& user)
{
	//user already is logged in
	if (m_loggedUsers.find(user) != m_loggedUsers.end())
		return false;

	m_loggedUsers.insert(user);
	return true;
}

/// <summary>
/// Removing a user from the room
/// </summary>
/// <param name="user">user to remove</param>
/// <returns>whether the remove succeeded (if user already not logged in, return false)</returns>
bool Room::removeUser(const LoggedUser& user)
{
	//if the user is already not is logged in
	if (m_loggedUsers.find(user) == m_loggedUsers.end())
		return false;

	m_loggedUsers.erase(user);
	return true;
}

/// <summary>
/// Return a vector of all users' usernames
/// </summary>
std::vector<std::string> Room::getAllUsers() const
{
	std::vector<std::string> allUsers;

	for (const auto& user : m_loggedUsers)
	{
		allUsers.push_back(user.getUsername());
	}

	return allUsers;
}