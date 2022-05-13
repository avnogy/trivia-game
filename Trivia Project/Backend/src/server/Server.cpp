#include "server/Server.h"
#include <thread>
#include <iostream>

/// <summary>
/// Creating  a new thread to handle new connections
/// </summary>
void Server::run()
{
	//creating a thread for the main operation of the server
#ifndef _DEBUG
	std::thread t_connector(&Communicator::startHandleRequest, this->m_communicator);
	t_connector.detach();
#else
	Communicator::instance().startHandleRequest();
#endif

	std::string input = "";
	while (input != "EXIT")
	{
		std::cin >> input;
	}
	//TODO: release resources on close
}

Server::Server() :
	m_database(new SqliteDataBase(DATABASE_PATH)), m_communicator(m_handlerFactory), m_handlerFactory(m_database)
{
}

Server::~Server()
{
	delete m_database;
}