#pragma once

/*
Put this macro inside every class to make it a singleton
*/
#define COPY_CONSTRUCTOR(className) className(const className&)
#define MOVE_CONSTRUCTOR(className) className(className&&)
#define ASSIGNMENT_OPERATOR(className) className& operator = (const className&)
#define MOVE_ASSIGNMENT_OPERATOR(className) className& operator = (className&&)
#define DELETE_CONSTRUCTOR(className) private: className() {};

#define MAKE_SINGLETON(className)							\
public:														\
	COPY_CONSTRUCTOR(className)			= delete;			\
	MOVE_CONSTRUCTOR(className)			= delete;			\
	ASSIGNMENT_OPERATOR(className)		= delete;			\
	MOVE_ASSIGNMENT_OPERATOR(className) = delete;			\
															\
	static className& instance()							\
	{														\
		static className m_instance;						\
		return m_instance;									\
	}														\
private: