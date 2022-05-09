#include "server/Communicator.h"
#include <thread>
#include <iostream>

#pragma warning(disable : 4996)

/// <summary>
/// Receiving a request from a socket.
/// </summary>
/// <param name="socket">socket to receive request from</param>
/// <returns>RequestInfo - struct to hold inforamtion about request</returns>
RequestInfo Communicator::recvRequest(Socket& socket)
{
	RequestInfo requestInfo;

	//get receival time
	time_t currentTime = time(NULL);
	requestInfo.receivalTime = ctime(&currentTime);

	//get id
	requestInfo.id = stoi(socket.recvString(1));

	//get buffer
	size_t contentSize = stoi(socket.recvString(4));
	requestInfo.buffer = socket.recvString(contentSize);

	return requestInfo;
}

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

	RequestInfo request = recvRequest(client);

	if (m_clients[*socket]->isRequestRelevant(request))
	{
		m_clients[*socket]->handleRequest(request);
	}
	else
	{
		client.send(JsonRequestPacketSerializer::serializeResponse(ErrorResponse()));
	}

	delete* socket;
	*socket = nullptr;
}

/// <summary>
/// Instantiating a new communicator.
/// </summary>
/// <param name="handlerFactory">reference to requestHandlerFactory</param>
Communicator::Communicator(RequestHandlerFactory& handlerFactory) :
	m_handlerFactory(handlerFactory)
{
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

		//saving new connection
		m_clients.insert({ newClient, new LoginRequestHandler() });

		//handling new connection in a separate thread
#ifndef _DEBUG
		std::thread t_handleNewClient(&Communicator::handleNewClient, this, &newClient);
		t_handleNewClient.detach();
#else
		handleNewClient(&newClient);
#endif
	}
}