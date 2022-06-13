#include "managers/GameManager/Game.h"

/// <summary>
/// Creating a new game
/// </summary>
/// <param name="questions">questions for games</param>
Game::Game(const std::queue<Question>& questions, const std::vector<std::string>& users) :
	m_questions(questions),
	m_currentQuestion(m_questions.front()),
	m_submitCount(0),
	m_sendCorrectAnswers(Game::sendCorrectAnswers, this) //creating a thread to send all players the correct answers
{
	for (const auto& user : users)
	{
		m_players.insert({ user, GameData() });
	}

	m_sendCorrectAnswers.detach();
}

/// <summary>
/// Check if all players jave submited an answer
/// </summary>
bool Game::isAllSubmited()
{
	if (m_submitCount.size() < m_players.size())
		return false;

	m_submitCount.clear();
	return true;
}

void Game::sendCorrectAnswers(Game* game)
{
	while (true)
	{
		bool isGameEnded = false;
		std::string correctAnswerResponse = "";

		//waiting until all players submited an answer
		while (!game->isAllSubmited())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		//assembling message to send to players
		correctAnswerResponse = JsonRequestPacketSerializer::instance().serializeResponse(
			MessageTypeResponse{
				game->getQuestions().size() <= 1 ? MessageTypeResponse::Type::GetGameResultsResponse: MessageTypeResponse::Type::CorrectAnswerResponse,
				JsonRequestPacketSerializer::instance().serializeResponse(CorrectAnswerResponse{ game->m_currentQuestion.getCorrectAnswer() })
			});

		game->nextQuestion();
		isGameEnded = game->getQuestions().size() <= 0;

		for (const auto& user : game->m_players)
		{
			Socket* userSocket = Communicator::instance().getSocket(user.first.getUsername());

			//sending question to all players
			userSocket->send(correctAnswerResponse);

			//if it is the last questions, send also the game results
			if (isGameEnded)
			{
				userSocket->send(JsonRequestPacketSerializer::instance().serializeResponse(
					GetGameResultsResponse{ GetGameResultsResponse::SUCCESS, game->getGameResults() }
					));
			}
		}

		if (isGameEnded)
			return;
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
const Question& Game::getQuestion() const
{
	return m_questions.front();
}

/// <summary>
/// making m_currectQuestion the next question
/// </summary>
void Game::nextQuestion()
{
	m_questions.pop();
	m_currentQuestion = m_questions.front();
}


/// <summary>
/// checking if the answer is correct, and getting the correct answer
/// </summary>
/// <param name="user">user that submitted the answer</param>
/// <param name="answer>the answer the user submitted</param>
/// <returns>SubmitAnswerResponse</returns>
void Game::submitAnswer(const LoggedUser& user, const std::string& answer)
{
	m_submitCountMutex.lock();
	m_submitCount.insert(user.getUsername());
	m_submitCountMutex.unlock();

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
