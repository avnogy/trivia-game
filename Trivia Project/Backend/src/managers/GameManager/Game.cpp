#include "managers/GameManager/Game.h"

/// <summary>
/// Creating a new game
/// </summary>
/// <param name="questions">questions for games</param>
Game::Game(const std::vector<Question>& questions, const std::vector<std::string>& users) :
	m_questions(questions)
{
	for (const auto& user : users)
	{
		m_players.insert({ user, GameData{m_questions[0]}});
	}
}

/// <summary>
/// checking if the answer is correct, and getting the correct answer
/// </summary>
/// <param name="user">user that submitted the answer</param>
/// <param name="answer>the answer the user submitted</param>
/// <returns>SubmitAnswerResponse</returns>
SubmitAnswerResponse Game::submitAnswer(const LoggedUser& user, const std::string& answer)
{
	std::string correctAnswer = m_players[user].currentQuestion.getCorrectAnswer();

	return SubmitAnswerResponse{
		(unsigned int)((correctAnswer == answer) ? 0 : 1),
		correctAnswer
	};
}

/// <summary>
/// Removing a player from a game
/// </summary>
/// <param name="user">user to remove</param>
void Game::removePlayer(const LoggedUser& user)
{
	m_players.erase(user);
}
