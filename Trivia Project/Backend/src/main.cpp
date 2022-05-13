#pragma comment (lib, "ws2_32.lib")

#include "server/WSAInitializer.h"
#include "server/Server.h"
#include <iostream>

int main()
{
	std::cout << " ----- Server -----" << std::endl;
	try
	{
		WSAInitializer wsaInit;

		Server::instance().run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	system("PAUSE");
	return 0;
}