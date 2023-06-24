#pragma once
#include "utils/utils.h"
#include "managers/RoomManager/RoomData.h"
#include "managers/LoggedUser.h"

class Room
{
private:
	const RoomData m_metadata;
	std::unordered_set<LoggedUser> m_loggedUsers;

public:
	Room() = default;
	Room(const RoomData& data, const LoggedUser& user);
	~Room();

	RoomData getRoomData() const;
	bool addUser(const LoggedUser& user);
	bool removeUser(const LoggedUser& user);
	std::vector<std::string> getAllUsers() const;
};