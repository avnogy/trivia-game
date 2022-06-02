#pragma once

struct LeaveRoomResponse
{
	enum : unsigned int
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};