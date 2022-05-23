#pragma once
#include "handlers/IRequestHandler.h"
#include "requests/LoginRequest.h"
#include "managers/LoginManager/LoginManager.h"
#include "handlers/MenuRequestHandler.h"
#include "handlers/RequestHandlerFactory.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
private:
	RequestResult login(const RequestInfo& requestInfo);
	RequestResult signup(const RequestInfo& requestInfo);

public:
	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;
};
