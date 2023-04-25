#pragma once

struct CreateRoomResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};