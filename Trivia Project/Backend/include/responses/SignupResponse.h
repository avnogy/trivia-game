#pragma once

struct SignupResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};