#include "managers/GameManager/Game.h"

/// <summary>
/// Creating a new game
/// </summary>
/// <param name="questions">questions for games</param>
Game::Game(const std::queue<Question>& questions, const std::vector<std::string>& users) :
	m_questions(questions), m_currentQuestion(m_questions.front())
{
	for (const auto& user : users)
	{
		m_players.insert({ user, GameData() });
	}
}

/// <summary>
/// Get all game results
/// </summary>
/// <returns>all game results</returns>
std::vector<PlayerResults> Game::getGameResults() const
{
	std::vector<PlayerResults> gameResults;

	for (const auto& player : m_players)
	{
		gameResults.push_back({
			player.first.getUsername(),
			player.second.correctAnswerCount,
			player.second.wrongAnswerCount,
			player.second.AverageAnswerTime
			});
	}
	return gameResults;
}

/// <summary>
/// Getting all questions
/// </summary>
/// <returns>all questions</returns>
std::queue<Question> Game::getQuestions() const
{
	return m_questions;
}

/// <summary>
/// getting the current question
/// </summary>
const Question& Game::getQuestion()
{
	m_currentQuestion = m_questions.front();
	m_questions.push(m_currentQuestion);
	m_questions.pop();
	return m_currentQuestion;
}

/// <summary>
/// checking if the answer is correct, and getting the correct answer
/// </summary>
/// <param name="user">user that submitted the answer</param>
/// <param name="answer>the answer the user submitted</param>
/// <returns>SubmitAnswerResponse</returns>
void Game::submitAnswer(const LoggedUser& user, const std::string& answer) 
{
	if (m_currentQuestion.getCorrectAnswer() == answer)
	{
		m_players[user].correctAnswerCount++;
	}
	else
	{
		m_players[user].wrongAnswerCount++;
	}
}

/// <summary>
/// Removing a player from a game
/// </summary>
/// <param name="user">user to remove</param>
void Game::removePlayer(const LoggedUser& user)
{
	m_players.erase(user);
}
