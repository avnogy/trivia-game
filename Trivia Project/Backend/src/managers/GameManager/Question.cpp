#include "infrastructure/database/Question.h"

/// <summary>
/// Creating a new quest class
/// </summary>
/// <param name="question">question</param>
/// <param name="possibleAnswers">array of all asnwers (correct in index 0)</param>
Question::Question(const std::string& question, const std::vector<std::string>& possibleAnswers) :
	m_question(question), m_possibleAnswers(possibleAnswers)
{
}

/// <summary>
/// Getting the question
/// </summary>
/// <returns>m_question</returns>
const std::string Question::getQuestion() const
{
	return m_question;
}

/// <summary>
/// Getting all possible answers
/// </summary>
/// <returns>m_possibleAnswers</returns>
const std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}

/// <summary>
/// Get the correct answer
/// </summary>
/// <returns>correct answers</returns>
const std::string Question::getCorrectAnswer() const
{
	return m_possibleAnswers[0];
}