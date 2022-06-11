#pragma once

struct UpdateResponse
{
	enum
	{
		SUCCESS,
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