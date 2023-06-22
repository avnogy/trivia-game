#pragma once
#include <string>

struct SubmitAnswerResponse
{
	enum
	{
		SUCCESS,
		FAILURE
	};
	unsigned int status;
};