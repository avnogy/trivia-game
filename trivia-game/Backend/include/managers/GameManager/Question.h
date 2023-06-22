#pragma once
#include <string>
#include <vector>
#include "infrastructure/json/json.hpp"

class Question
{
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers; //correct in index 0

public:
	Question() = default;
	Question(const std::string& question, const std::vector<std::string>& possibleAnswers);
	Question& operator = (const Question& other);

	const std::string getQuestion() const;
	const std::vector<std::string> getPossibleAnswers() const;
	const std::string getCorrectAnswer() const;
};
