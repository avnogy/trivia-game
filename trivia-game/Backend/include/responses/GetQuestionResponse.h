#pragma once
#include "managers/GameManager/Question.h"

struct GetQuestionResponse
{
	enum
	{
		SUCCESS
	};
	unsigned int status;
	Question question;
};