#include "managers/RoomManager/Room.h"

/// <summary>
/// getter for room data
/// </summary>
/// <returns></returns>
RoomData Room::getRoomData() const
{
	return m_metadata;
}

/// <summary>
/// Adding a new user to the room
/// </summary>
/// <param name="user">user to add</param>
/// <returns>whether the addition succeeded (if user already is logged in, return false)</returns>
bool Room::addUser(const LoggedUser& user)
{
	//insert returns true if operation was successful
	return m_loggedUsers.insert(user).second;
}

/// <summary>
/// Removing a user from the room
/// </summary>
/// <param name="user">user to remove</param>
/// <returns>whether the remove succeeded (if user already not logged in, return false)</returns>
bool Room::removeUser(const LoggedUser& user)
{
	//erase returns the status of the operation
	return m_loggedUsers.erase(user);
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

Room::Room(const RoomData& data, const LoggedUser& user) : m_metadata(data)
{
	m_loggedUsers.insert(user);
}

Room::~Room()
{
}