#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"

class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo requestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};
