#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Socket.h"
#include <iostream>

int main()
{
	std::cout << " ----- Server -----" << std::endl;
	try
	{
		WSAInitializer wsaInit;
		Socket server;

		server.bind(9876);
		server.listen();

		Socket client = server.accept();

		std::cout << client.recv(5) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}