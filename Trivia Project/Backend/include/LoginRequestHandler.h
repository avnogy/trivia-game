#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : IRequestHandler
{
	bool isRequestRelevant(RequestInfo requestInfo) override;
	RequestResult handleRequest(RequestInfo requestInfo) override;
};
