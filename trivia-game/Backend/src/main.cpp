#pragma comment (lib, "ws2_32.lib")
#include "infrastructure/WSAInitializer.h"
#include "infrastructure/Server.h"
#include "utils/utils.h"

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