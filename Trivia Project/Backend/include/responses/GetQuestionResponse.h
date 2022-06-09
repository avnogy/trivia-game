#pragma once
#include "managers/GameManager/Question.h"

struct GetQuestionResponse
{
	unsigned int status;
	Question question;
};