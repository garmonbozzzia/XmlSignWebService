/// @file
/// @brief Файл содержит определение класса анализатора командной строки.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef CMDLINEPARSER_CMDLINEPARSER_H
#define CMDLINEPARSER_CMDLINEPARSER_H

#include <list>
#include <iostream>
#if defined(_WIN32)
#include <tchar.h>
#endif
#include "defines.h"
#include "parserdefs.h"
#include "flag.h"

namespace cmdlineparser{

	using flag::IFlagImpl;
	using flag::IFlag;

	
	struct CmdLineInput
	{
		CmdLineInput( int _argc, TCHAR **_argv ): argc( _argc ), argv( _argv )
		{
		} 
		int argc; 
		TCHAR **argv;
	};


	class CmdLineParser
	{
		typedef IFlagImpl* FlagPtr;
		typedef std::list<FlagPtr> FlagList;

	public:
		CmdLineParser();
		void AddFlag( IFlag * flag );
		void RemoveFlag( IFlag * flag );
		void SetDefault();
		void SetCmdLine( const CmdLineInput& );
		void SetCmdLine( int argc, TCHAR* const argv[] );
		void Parse();
		void PrintHelp() const;
	private:
		void SetModuleName( const char* fullName );

	private:
		FlagList flags_;
		Args args_;
		Flag<bool> default_;
		Flag<bool> help_;
		std::string moduleName_;
	};

} // namespace cmdlineparser
using cmdlineparser::CmdLineParser;
using cmdlineparser::CmdLineInput;

#endif // CMDLINEPARSER_CMDLINEPARSER_H