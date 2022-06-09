#pragma once
#include <string>

struct SubmitAnswerResponse
{
	enum
	{
		SUCCESS
	};
	unsigned int status;
	//unsigned int correctAnswerId;
	std::string correctAnswer;
};