#pragma once
#include <vector>
#include "managers/RoomManager/RoomData.h"

struct GetRoomsResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
	std::vector<RoomData> rooms;
};