#pragma once
#include "managers/GameManager/Question.h"

struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int AverageAnswerTime;
};

