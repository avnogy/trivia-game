#include "managers/RoomManager/RoomManager.h"

/// <summary>
/// creates a room and adds it to the vector
/// </summary>
/// <param name="user"></param>
/// <param name="data"></param>
/// <returns></returns>
bool RoomManager::createRoom(const LoggedUser& user, const RoomData& data)
{
	//the second item in the pair is the state of the operation
	return m_rooms.insert({ data.id, Room(data, user) }).second;
}

/// <summary>
/// deletes a room from the vector and returns state
/// </summary>
/// <param name="ID"></param>
/// <returns></returns>
bool RoomManager::deleteRoom(const int& ID)
{
	//erase returns the status of the operation
	return (m_rooms.erase(ID));
}

/// <summary>
/// returns the state of a room
/// </summary>
/// <param name="ID"></param>
/// <returns></returns>
unsigned int RoomManager::getRoomState(const int& ID)
{
	return (m_rooms[ID].getRoomData().isActive) ? GAME_ACTIVE : WAITING_TO_START_GAME;
}

/// <summary>
/// returns a vector containing all the rooms
/// </summary>
/// <returns></returns>
std::vector<RoomData> RoomManager::getRooms() const
{
	//putting the map values in a vector
	std::vector<RoomData> rooms_vec;
	for (const auto& pair : m_rooms)
		rooms_vec.push_back(pair.second.getRoomData());
	return rooms_vec;
}
