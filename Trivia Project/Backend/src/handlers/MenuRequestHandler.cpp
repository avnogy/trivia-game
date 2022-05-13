#include "handlers/MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	return RequestResult();
}