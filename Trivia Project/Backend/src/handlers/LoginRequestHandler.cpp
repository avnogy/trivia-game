#include "handlers/LoginRequestHandler.h"

/// <summary>
/// Instantiating a new LoginRequestHandler
/// </summary>
/// <param name="loginManager"></param>
/// <param name="requestHandlerFactory"></param>
LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory* requestHandlerFactory) :
	m_loginManager(loginManager), m_handlerFactory(*requestHandlerFactory)
{
}

/// <summary>
/// The function will call the loginManager's login method.
/// </summary>
/// <param name="requestInfo">information about login request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	m_loginManager.login(request.username, request.password);

	return RequestResult(); //update in future - not in this version
}

/// <summary>
/// The function will call the loginManager's signup method.
/// </summary>
/// <param name="requestInfo">information about signup request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo) const
{
	SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
	m_loginManager.signup(request.username, request.password, request.email);

	return RequestResult(); //update in future - not in this version
}

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory* requestHandlerFactory)
{
}

/// <summary>
/// Check if the request is a login request or a signup request
/// </summary>
/// <param name="requestInfo">struct containing request information</param>
/// <returns>whether the reqeust is login or signup</returns>
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	return (requestInfo.id == LoginRequestId) || (requestInfo.id == SignupRequestId);
}

/// <summary>
/// Check whether the request is login or signup and calls the right methods to handle request
/// </summary>
/// <param name="requestInfo">inforamtion about the request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo) const
{
	RequestResult requestResult;

	switch (requestInfo.id)
	{
	case LoginRequestId:
		requestResult = login(requestInfo); break;

	case SignupRequestId:
		requestResult = signup(requestInfo); break;
	}

	return requestResult;
}