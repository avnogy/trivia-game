#pragma once
#include <string>
#include <vector>

struct AddQuestionRequest
{
	std::string question;
	std::vector<std::string> possibleAnswers;
	std::string correctAnswer;
};