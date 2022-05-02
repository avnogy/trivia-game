#include "handlers/LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return false;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	return RequestResult();
}