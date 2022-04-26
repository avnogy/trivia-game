#include "Communicator.h"
#include <thread>
#include <iostream>

/// <summary>
/// Start listenning to new connections
/// </summary>
void Communicator::bindAndListen()
{
	m_serverSocket.bind(PORT);
	m_serverSocket.listen();
}

/// <summary>
/// Handling new connections
/// </summary>
/// <param name="socket"></param>
void Communicator::handleNewClient(Socket** socket)
{
	Socket& client = **socket;

	//receiving message
	unsigned short status = stoi(client.recv(1));
	unsigned int contentSize = stoi(client.recv(4));
	std::string content = client.recv(contentSize);

	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(content);
	std::cout << loginRequest.username << "\t" << loginRequest.password << std::endl;

	*socket = nullptr;
	delete* socket;
}

/// <summary>
/// - Accepting new connections
/// - Handling them in a new thread
/// - inserting them to clients map
/// </summary>
void Communicator::startHandleRequest()
{
	bindAndListen();
	while (true)
	{
		//accepting new connections
		Socket* newClient = m_serverSocket.accept();

		//handling new connection in a separate thread
		std::thread t_handleNewClient(&Communicator::handleNewClient, this, &newClient);
		t_handleNewClient.detach();

		//saving new connection
		m_clients.insert({ newClient, nullptr });
	}
}