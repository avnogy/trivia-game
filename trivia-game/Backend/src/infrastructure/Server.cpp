#include "infrastructure/Server.h"
#include <thread>
#include <iostream>

/// <summary>
/// Creating  a new thread to handle new connections
/// </summary>
void Server::run()
{
	//creating a thread for the main operation of the server
	std::thread t_connector(&Communicator::startHandleRequest, std::ref(Communicator::instance()));
	t_connector.detach();
	
	std::string input = "";
	while (input != "EXIT")
	{
		std::cin >> input;
	}
}