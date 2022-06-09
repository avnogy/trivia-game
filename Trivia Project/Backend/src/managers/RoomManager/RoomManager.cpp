#include "managers/RoomManager/RoomManager.h"

/// <summary>
/// Getting a room
/// </summary>
/// <param name="roomId"></param>
/// <returns></returns>
Room& RoomManager::getRoom(unsigned int roomId)
{
	return m_rooms[roomId];
}

/// <summary>
///	Getting the next room id.
/// </summary>
/// <returns>biggest room id + 1</returns>
unsigned int RoomManager::getNextRoomId() const
{
	if (m_rooms.size() == 0)
		return 0;
	return m_rooms.rbegin()->first + 1;
}

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
/// Adding a new user to a room
/// </summary>
/// <param name="user">user to add to room</param>
/// <param name="roomID">room to add the user to</param>
/// <returns>whether succeessfully added user</returns>
bool RoomManager::joinRoom(const LoggedUser& user, unsigned int roomID)
{
	return m_rooms[roomID].addUser(user);
}

/// <summary>
/// returns the state of a room
/// </summary>
/// <param name="ID"></param>
/// <returns></returns>
unsigned int RoomManager::getRoomState(const int& ID) const
{
	return (m_rooms.at(ID).getRoomData().isActive) ? GAME_ACTIVE : WAITING_TO_START_GAME;
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

/// <summary>
/// Getting all players in a room
/// </summary>
/// <param name="ID">id of the room</param>
/// <returns>all usernames of all players in a room</returns>
std::vector<std::string> RoomManager::getPlayersInRoom(const int& ID) const
{
	return m_rooms.at(ID).getAllUsers();
}