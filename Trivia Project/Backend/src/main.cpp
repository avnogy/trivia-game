#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include <iostream>

int main()
{
	std::cout << " ----- Server -----" << std::endl;
	try
	{
		WSAInitializer wsaInit;
		Server server;

		server.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}