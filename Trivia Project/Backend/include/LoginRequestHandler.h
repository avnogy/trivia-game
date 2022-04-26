#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) const override;
};
