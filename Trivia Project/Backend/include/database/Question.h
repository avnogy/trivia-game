#pragma once
#include <string>
#include <vector>

class Question
{
private:
	const std::string m_question;
	const std::vector<std::string> m_possibleAnswers; //correct in index 0

public:
	Question(const std::string& question, const std::vector<std::string>& possibleAnswers);

	const std::string getQuestion() const;
	const std::vector<std::string> getPossibleAnswers() const;
	const std::string getCorrectAnswer() const;
};