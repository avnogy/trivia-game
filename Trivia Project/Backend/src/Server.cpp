#include "Server.h"
#include <thread>
#include <iostream>

/// <summary>
/// Creating  a new thread to handle new connections
/// </summary>
void Server::run()
{
	//creating a thread for the main operation of the server
	std::thread t_connector(&Communicator::startHandleRequest, this->m_communicator);
	t_connector.detach();

	std::string input = "";
	while (input != "EXIT")
	{
		std::cin >> input;
	}
	//TODO: release resources on close
}