#pragma once
#include <string>
#include "handlers/IRequestHandler.h"

#define ReturnNewRequestResult(response, nextHandler)							\
{																			\
	RequestResult requestResult = RequestResult{ response, nextHandler };	\
	delete this;															\
	return requestResult;													\
}

class IRequestHandler;

struct RequestResult
{
	std::string response;
	IRequestHandler* newHandler;
};