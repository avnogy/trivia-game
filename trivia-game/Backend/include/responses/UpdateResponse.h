#pragma once

struct UpdateResponse
{
	enum
	{
		SUCCESS=1,
		FAILURE
	};
	enum
	{
		StartGame,
		LeaveRoom
	};
	unsigned int status;
	unsigned int type;
};