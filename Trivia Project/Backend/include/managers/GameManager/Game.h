#pragma once
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "infrastructure/Communicator.h"
#include "infrastructure/json/JsonRequestPacketSerializer.h"
#include "managers/GameManager/Question.h"
#include "managers/GameManager/GameData.h"
#include "managers/LoggedUser.h"
#include "responses/SubmitAnswerResponse.h"
#include "managers/GameManager/Question.h"
#include "responses/GetGameResultsResponse.h"
#include "handlers/GameRequestHandler.h"

#include <thread>
#include <mutex>

class Game
{
private:
	std::queue<Question> m_questions;
	Question m_currentQuestion;
	std::unordered_map<LoggedUser, GameData> m_players;

	std::unordered_set<std::string> m_submitCount;
	std::mutex m_submitCountMutex;
	std::thread m_sendCorrectAnswers;
	static std::vector<PlayerResults> sortResultsByWinner(std::vector<PlayerResults> v);
public:
	Game(const std::queue<Question>& questions, const std::vector<std::string>& users);

	bool isAllSubmited();
	bool isAlreadySubmited(const LoggedUser& user) const;

	std::queue<Question> getQuestions() const;
	const Question&		 getQuestion() const;
	void				 nextQuestion();
	std::vector<PlayerResults> getGameResults() const;

	void submitAnswer(const LoggedUser& user, const std::string& answer,const float timeToAnswer) ;
	void removePlayer(const LoggedUser& user);

	static void sendCorrectAnswers(Game* game);
};

