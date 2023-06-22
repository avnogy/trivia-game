#pragma once
#include "managers/RoomManager/Room.h"
#include "utils/Singleton.h"
#include <map>
#define WAITING_TO_START_GAME 42
#define GAME_ACTIVE 43

class RoomManager
{
	MAKE_SINGLETON(RoomManager);
	DELETE_CONSTRUCTOR(RoomManager);

private:
	std::map<unsigned int, Room> m_rooms;

public:
	bool createRoom(const LoggedUser& user, const RoomData& data);
	bool deleteRoom(const int& ID);
	bool joinRoom(const LoggedUser& user, unsigned int roomID);

	Room& getRoom(unsigned int roomId);
	unsigned int getNextRoomId() const;
	unsigned int getRoomState(const int& ID) const;
	std::vector<RoomData> getRooms() const;
	std::vector<std::string> getPlayersInRoom(const int& ID) const;
};
