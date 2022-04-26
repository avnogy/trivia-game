#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"

class IRequestHandler
{
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) const = 0;
};
