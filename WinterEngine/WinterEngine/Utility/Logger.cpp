#include "Logger.h"
#include <iostream>
#include <windows.h>

namespace Logger
{
	std::map<std::string, LogType> LogTypes;
	HANDLE  hConsole; // TODOMH release this?
}

void Logger::Initialize()
{
	// OPEN console
	AllocConsole();
	freopen( "CONOUT$", "w", stdout );
}

void Logger::RegisterLoggerType( const std::string& name, const std::string& parent )
{
	if( parent != "" )
	{
		// TODOMH implement parents
	}

	else
	{
		// No parent was supplied so create LogType with no parent.
		LogType lt;
		lt.Parent = "";
		LogTypes.emplace( name.c_str(), lt );
	}

}

void Logger::Log( const std::string& msg, const std::string& msgRegisterName, LoggerType logType )
{
	std::map<std::string, LogType>::const_iterator cit = LogTypes.find( msgRegisterName );
	
	// Only log things that we are interessted in
	if( cit == LogTypes.end() )
	{
		return;
	}

	hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	
	// TODOMH Fix color class
	const int red = 195;
	const int purple = 21;
	const int green = 2;
	const int brightGreen = 10;
	const int white = 7;
	const int grey = 8;
	const int yellow = 14;

	/* // Playing around with colors
	for( int k = 1; k < 255; k++ )
	{
		SetConsoleTextAttribute( hConsole, k );

		std::cout << "WARNING ";
	}
	*/

	switch( logType )
	{
		// TODOMH write this to file instead, for now only in console
		case LoggerType::MSG_INFO:
		{
									 SetConsoleTextAttribute( hConsole, white );
									 std::cout << "INFO " + msgRegisterName + ": ";
									 std::cout << msg + "\n";
									 break;
		};

		case LoggerType::MSG_WARNING:
		{
										SetConsoleTextAttribute( hConsole, yellow );
										std::cout << "WARNING " + msgRegisterName + ": ";
										std::cout << msg + "\n";
										break;
		};

		case LoggerType::MSG_ERROR:
		{
									  SetConsoleTextAttribute( hConsole, red );
									  std::cout << "ERROR " + msgRegisterName + ": ";
									  std::cout << msg + "\n";
									  #ifdef _WIN32
									    // Press enter in console to continue program
										system( "pause" );	// TODO... Fix better way of pausing that works for windows and linux
									  #endif
									  break;
		}

		case LoggerType::MSG_DEBUG:
		{
									  SetConsoleTextAttribute( hConsole, green );
									  std::cout << "DEBUG " + msgRegisterName + ": ";
									  std::cout << msg + "\n";
									  break;
		}

		case LoggerType::ALL:
		{
								SetConsoleTextAttribute( hConsole, red );
								std::cout << "Don't use this logger type! " << "\n";
								break;
		}
	}
}
