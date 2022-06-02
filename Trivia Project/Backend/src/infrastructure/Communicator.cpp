#include "infrastructure/Communicator.h"
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
/// <param name="socket">socket to handle</param>
void Communicator::handleNewClient(Socket* socket)
{
	try
	{
		while (true)
		{
			RequestInfo request = recvRequest(*socket);
			RequestResult result;

			if (m_clients[socket]->isRequestRelevant(request))
			{
				result = m_clients[socket]->handleRequest(request);  //handling client
				socket->send(result.response);						 //sending client response
				m_clients[socket] = result.newHandler;			     //updating client handler
			}
			else
			{
				socket->send(JsonRequestPacketSerializer::serializeResponse(ErrorResponse()));
			}

			std::cout << result.response << '\n' << std::endl;
		}
	}
	catch (...)
	{
	}

	m_clients.erase(socket);
	delete socket;
}

/// <summary>
/// Binding the username to the socket/
/// </summary>
/// <param name="username">username of a client</param>
/// <param name="socket">socket of the client</param>
void Communicator::bindUsernameToSocket(const std::string& username, IRequestHandler* requestHandler)
{
	for (auto& it : m_clients)
	{
		if (it.second == requestHandler)
		{
			usernameToSocket[username] = it.first;
			break;
		}
	}
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
		m_clients.insert({ newClient, RequestHandlerFactory::instance().createLoginRequestHandler() });

		//handling new connection in a separate thread
#ifndef _DEBUG
		std::thread t_handleNewClient(&Communicator::handleNewClient, this, newClient);
		t_handleNewClient.detach();
#else
		handleNewClient(newClient);
#endif
	}
}