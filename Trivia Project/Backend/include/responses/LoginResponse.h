#pragma once

struct LoginResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};