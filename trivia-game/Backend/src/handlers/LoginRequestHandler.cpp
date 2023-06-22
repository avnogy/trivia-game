#include "handlers/LoginRequestHandler.h"

/// <summary>
/// The function will call the loginManager's login method.
/// </summary>
/// <param name="requestInfo">information about login request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo) const
{
	LoginRequest request = DESERIALIZE(LoginRequest, requestInfo.buffer);
	bool result = LoginManager::instance().login(request.username, request.password);

	switch (result)
	{
	case true:
		Communicator::instance().bindUsernameToSocket(request.username, (IRequestHandler*)this); //updating communicator with username
		
		ReturnNewRequestResult(
			SERIALIZE(LoginResponse{LoginResponse::SUCCESS}),
			RequestHandlerFactory::instance().createMenuRequestHandler({ request.username })
		);
		

	case false:
		return RequestResult{
			SERIALIZE(LoginResponse{LoginResponse::FAILURE}),
			(IRequestHandler*)this
		};
	}
}

/// <summary>
/// The function will call the loginManager's signup method.
/// </summary>
/// <param name="requestInfo">information about signup request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo) const
{
	SignupRequest request = DESERIALIZE(SignupRequest, requestInfo.buffer);
	bool result = LoginManager::instance().signup(request.username, request.password, request.email);

	switch (result)
	{
	case true:
		ReturnNewRequestResult(
			SERIALIZE(SignupResponse{SignupResponse::SUCCESS}),
			RequestHandlerFactory::instance().createLoginRequestHandler()
		);
	case false:
		return RequestResult{
			SERIALIZE(SignupResponse{SignupResponse::FAILURE}),
			(IRequestHandler*)this
		};
	}
}

/// <summary>
/// This function checks if the request is a login request or a signup request
/// </summary>
/// <param name="requestInfo">struct containing request information</param>
/// <returns>whether the reqeust is login or signup</returns>
bool LoginRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	switch (requestInfo.id)
	{
	case IDS::LoginRequest: case IDS::SignupRequest:
		return true;
	default:
		return false;
	}
}

/// <summary>
/// This functions checks whether the request is login or signup and calls the right methods to handle request
/// </summary>
/// <param name="requestInfo">inforamtion about the request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	switch (requestInfo.id)
	{
	case IDS::LoginRequest:
		return login(requestInfo);

	case IDS::SignupRequest:
		return signup(requestInfo); break;
	}
}
