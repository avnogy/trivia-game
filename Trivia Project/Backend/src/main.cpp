#pragma comment (lib, "ws2_32.lib")

#include "server/WSAInitializer.h"
#include "server/Server.h"
#include <iostream>

int main()
{
	std::cout << " ----- Server -----" << std::endl;
	try
	{
		//WSAInitializer wsaInit;

		//Server::instance().run();

		auto questions = IDatabase::instance()->getQuestions();

		for (auto question : questions)
		{
			auto q = question.getQuestion();
			auto possible = question.getPossibleAnswers();

			std::cout << q << '\n';
			for (auto i : possible)
				std::cout << " - " << i << '\n';

			std::cout << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}