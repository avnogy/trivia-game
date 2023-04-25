#pragma once

struct JoinRoomResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};