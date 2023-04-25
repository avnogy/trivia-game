#pragma once

struct LogoutResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};