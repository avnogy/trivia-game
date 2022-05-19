#pragma once
#include <vector>
#include "managers/RoomManager/RoomData.h"

struct getRoomResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};