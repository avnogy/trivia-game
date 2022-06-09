#pragma once
#include <string>

struct SubmitAnswerResponse
{
	unsigned int status;
	//unsigned int correctAnswerId;
	std::string correctAnswer;
};