#pragma once
#include <string>

struct LoginResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};