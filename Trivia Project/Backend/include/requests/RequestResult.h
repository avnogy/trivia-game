#pragma once
#include <string>
#include "handlers/IRequestHandler.h"

class IRequestHandler;

struct RequestResult
{
	std::string response;
	IRequestHandler* newHandler;
};