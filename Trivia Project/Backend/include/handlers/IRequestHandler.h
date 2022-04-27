#pragma once
#include "requests/RequestInfo.h"
#include "requests/RequestResult.h"

class IRequestHandler
{
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const = 0;
};
