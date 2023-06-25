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

bool Game::isAlreadySubmited(const LoggedUser& user) const
{
	return m_submitCount.count(user.getUsername()) != 0;
}

void Game::sendCorrectAnswers(Game* game)
{
	int count = game->getQuestions().size(); //number of questions in game
	std::string correctAnswerResponse = "";

	while (true)
	{
		//waiting until all players submit their answers
		while (!game->isAllSubmited())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		//assembling message to send to players
		correctAnswerResponse = SERIALIZE((
			MessageTypeResponse{
				game->getQuestions().size() <= 1 ? MessageTypeResponse::Type::GetGameResultsResponse : MessageTypeResponse::Type::CorrectAnswerResponse, //if last question, send GetGameResultsResponse
				JsonRequestPacketSerializer::instance().serializeResponse(CorrectAnswerResponse{ game->m_currentQuestion.getCorrectAnswer() }) }
		));

		//sending message to players
		for (auto& user : game->m_players)
		{
			Socket* userSocket = Communicator::instance().getSocket(user.first.getUsername());
			userSocket->send(correctAnswerResponse);
		}

		//if game ends, send end results.
		//else continue game
		if (game->getQuestions().size() <= 1)
		{
			for (auto& user : game->m_players)
			{
				//calculating and updating average answer time for each player
				user.second.AverageAnswerTime /= count;
			}
			for (auto& user : game->m_players)
			{
				//sending end results
				Socket* userSocket = Communicator::instance().getSocket(user.first.getUsername());
				userSocket->send(JsonRequestPacketSerializer::instance().serializeResponse(
					GetGameResultsResponse{ GetGameResultsResponse::SUCCESS, sortResultsByWinner(game->getGameResults()) }
				));
			}
			for (const auto& result : game->getGameResults())
			{
				//adding result to the database
				if (!StatisticsManager::instance().addUserStatistic(result))
				{
					throw DatabaseError(__FUNCTION__" - Sql request failed.");
				}
			}
			return;
		}
		else
		{
			game->nextQuestion();
		}
	}
}

/// <summary>
/// returns a result array sorted by winner
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
std::vector<PlayerResults> Game::sortResultsByWinner(std::vector<PlayerResults> v)
{
	//compares two users by avrage time and correctness of answers
	auto compare = [](PlayerResults a, PlayerResults b)
	{
		return (a.correctAnswerCount /
			(a.wrongAnswerCount + a.averageAnswerTime) == 0 ? 1 : (a.wrongAnswerCount * 3 + a.averageAnswerTime)) <
			(b.correctAnswerCount /
				(b.wrongAnswerCount + b.averageAnswerTime) == 0 ? 1 : (b.wrongAnswerCount * 3 + b.averageAnswerTime));
	};
	std::sort(v.begin(), v.end(), compare);
	return v;
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
void Game::submitAnswer(const LoggedUser& user, const std::string& answer, const float timeToAnswer)
{
	m_submitCountMutex.lock();
	m_submitCount.insert(user.getUsername());
	m_submitCountMutex.unlock();

	m_players[user].AverageAnswerTime += timeToAnswer;
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