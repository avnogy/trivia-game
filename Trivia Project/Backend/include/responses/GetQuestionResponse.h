#pragma once
#include "infrastructure/database/Question.h"

struct GetQuestionResponse
{
	unsigned int status;
	Question question;
};