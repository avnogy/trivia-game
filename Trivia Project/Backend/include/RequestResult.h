#pragma once
#include <string>
#include "IRequestHandler.h"

struct RequestResult
{
	std::string response;
	IRequestHandler* newHandler;
};