#pragma once
#include "server/Communicator.h"

class Server
{
private:
	Communicator m_communicator;

public:
	void run();
};
