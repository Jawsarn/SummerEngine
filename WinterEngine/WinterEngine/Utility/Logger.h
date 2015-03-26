#pragma once
#include <string>
#include <vector>
#include <map>

enum LoggerType
{
	MSG_INFO,
	MSG_WARNING,
	MSG_ERROR,
	MSG_DEBUG,
	ALL,
};

struct LogType
{
	std::string Parent;
	std::vector<std::string> Children;
};

namespace Logger
{
	void Initialize();
	void RegisterLoggerType( const std::string& name, const std::string& parent = "" );
	void Log( const std::string& msg, const std::string& msgRegisterName, LoggerType logType = LoggerType::MSG_INFO );

};

