#pragma once
#include <string>
#include "IRequestHandler.h"

class IRequestHandler;

struct RequestResult
{
	std::string response;
	IRequestHandler* newHandler;
};