#pragma once
#include "handlers/IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
