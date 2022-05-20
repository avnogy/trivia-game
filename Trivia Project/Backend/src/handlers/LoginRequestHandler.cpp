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
RequestResult LoginRequestHandler::login(const RequestInfo& requestInfo)
{
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
	bool result = m_loginManager.login(request.username, request.password);

	std::cout
		<< "username: " << request.username << '\n'
		<< "password: " << request.password << '\n';

	switch (result)
	{
	case true:
		return RequestResult{
		JsonRequestPacketSerializer::serializeResponse(LoginResponse{LoginResponse::SUCCESS}),
		new MenuRequestHandler()
		};// m_handlerFactory.createMenuRequestHandler()

	case false:
		return RequestResult{
			JsonRequestPacketSerializer::serializeResponse(LoginResponse{LoginResponse::FAILURE}),
			this
		};
	}
}

/// <summary>
/// The function will call the loginManager's signup method.
/// </summary>
/// <param name="requestInfo">information about signup request</param>
/// <returns>request result</returns>
RequestResult LoginRequestHandler::signup(const RequestInfo& requestInfo)
{
	SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buffer);
	bool result = m_loginManager.signup(request.username, request.password, request.email);

	std::cout
		<< "username: " << request.username << '\n'
		<< "password: " << request.password << '\n'
		<< "email: " << request.email << '\n';

	switch (result)
	{
	case true:
		return RequestResult{
			JsonRequestPacketSerializer::serializeResponse(SignupResponse{SignupResponse::SUCCESS}),
			RequestHandlerFactory::instance().createLoginRequestHandler()
		};
	case false:
		return RequestResult{
			JsonRequestPacketSerializer::serializeResponse(SignupResponse{SignupResponse::FAILURE}),
			this
		};
	}
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
RequestResult LoginRequestHandler::handleRequest(const RequestInfo& requestInfo)
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