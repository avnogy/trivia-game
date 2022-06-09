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
std::vector<Question> Game::getQuestions() const
{
	return m_questions;
}

/// <summary>
/// Getting currect question for a user
/// </summary>
/// <param name="user"></param>
/// <returns>currect question</returns>
Question Game::getQuestionForUser(const LoggedUser& user) const
{
	return m_players.at(user).currentQuestion;
}

/// <summary>
/// checking if the answer is correct, and getting the correct answer
/// </summary>
/// <param name="user">user that submitted the answer</param>
/// <param name="answer>the answer the user submitted</param>
/// <returns>SubmitAnswerResponse</returns>
void Game::submitAnswer(const LoggedUser& user, const std::string& answer) 
{
	std::string correctAnswer = m_players[user].currentQuestion.getCorrectAnswer();
	if (correctAnswer == answer)
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
