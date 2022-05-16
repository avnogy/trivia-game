#pragma once 
#include "managers/RoomManager/Room.h"
#include <map>
#define WAITING_TO_START_GAME 42
#define GAME_ACTIVE 43

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	bool createRoom(const LoggedUser& user, const RoomData& data);
	bool deleteRoom(const int& ID);
	unsigned int getRoomState(const int& ID);
	std::vector<RoomData> getRooms() const;

private:
	std::map<unsigned int, Room> m_rooms;
};
