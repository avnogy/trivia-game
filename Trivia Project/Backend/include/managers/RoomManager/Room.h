#pragma once

#include "managers/RoomManager/RoomData.h"
#include <unordered_set>
#include "managers/LoggedUser.h"

class Room
{
private:
	const RoomData m_metadata;
	std::unordered_set<LoggedUser> m_loggedUsers;

public:
	bool addUser(const LoggedUser& user);
	bool removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers() const;
};