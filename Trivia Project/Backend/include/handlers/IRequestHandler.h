#pragma once
#include "requests/RequestInfo.h"
#include "requests/RequestResult.h"

#include <iostream>
#include "json/JsonRequestPacketDeserializer.h"

class RequestResult;

class IRequestHandler
{
protected:
	enum {
		LoginRequestId,
		SignupRequestId,
	};

public:
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) = 0;
};
