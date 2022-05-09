#pragma once
#include "handlers/IRequestHandler.h"
#include "requests/LoginRequest.h"
#include "managers/LoginManager.h"

//deleting when creating reqeust handler factory
typedef RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;

private:
	RequestResult login(const RequestInfo& requestInfo) const;
	RequestResult signup(const RequestInfo& requestInfo) const;

public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory* requestHandlerFactory);

	bool isRequestRelevant(const RequestInfo& requestInfo) const override;
	RequestResult handleRequest(const RequestInfo& requestInfo) const override;
};
