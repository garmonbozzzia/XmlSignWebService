/// @file
/// @brief Файл содержит определение методов класса настроек интегрального теста.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "settings.h"

#if defined(__unix__)
// Quite rude definition but it fits the needs of this module.
#define _T(x) x
#endif

Settings::Settings( const CmdLineInput& _cmd, const ProviderInfo& _provInfo )
: providerInfo_( _provInfo )
{
     ParseCmdLine( _cmd );
}


void Settings::ParseCmdLine( const CmdLineInput& _cmd )
{
     LogFlag logStream( "log stream", "-l", _T( "cout" ) );
     //ContainerFlag container( "container", "-c", _T( "test.container" ) );
     ContainerFlag container( "container", "-c", _T( "C:\\Work\\certificate\\le-c60c3405-7918-479e-a4fe-e941118cc83e" ) );
     MessageFlag messageFile( "message file", "-m", _cmd.argv[0] );
     CspCallStrategyFlag cspDirectCallFlag( "call csp directly ", "-dc", true );
     
     static const int DEFAULT_STRESS_TEST_ITER_NUM = 1000;
     IterationsNumFlag iterationsNum( "stress test iterations num", "-s", DEFAULT_STRESS_TEST_ITER_NUM );
	
     CmdLineParser parser;
     try
     {
          parser.AddFlag( &container );
          parser.AddFlag( &logStream );
          parser.AddFlag( &messageFile );
          parser.AddFlag( &iterationsNum );
          parser.AddFlag( &cspDirectCallFlag );
          parser.SetCmdLine( _cmd );
          parser.Parse();
     }
     catch( cmdlineparser::exception::NoArgs& )
     {
          parser.SetDefault();
     }
     catch( cmdlineparser::exception::NeedHelp& )
     {
          parser.PrintHelp();
#if defined(__unix__)
	  throw string_exception( ">help" );
#else
          throw std::exception( ">help" );
#endif
     }
     catch( cmdlineparser::exception::Base& )
     {
          parser.PrintHelp();
          throw;
     }

     SetContainer( container );
     SetMessageFile( messageFile );
     SetLogStream( logStream );
     SetIterationsNum( iterationsNum );
     SetCspCallStrategy( cspDirectCallFlag );

}


LPCTSTR Settings::Container() const
{
     return container_.c_str();
}

// LPCTSTR Settings::ProviderName() const
// {
//      return providerInfo_.Name();
// }
// 
// DWORD Settings::ProviderType() const
// {
//      return providerInfo_.Type();
// }

std::ostream& Settings::LogStream() const
{
     return *logStream_;
}

LPCTSTR Settings::MessageFile() const
{
     return messageFile_.c_str();
}

void Settings::SetContainer( const ContainerFlag& _flag )
{
     container_ = _flag.GetVal();
}

void Settings::SetMessageFile( const MessageFlag& _flag )
{
     messageFile_ = _flag.GetVal();
}

void Settings::SetLogStream( const LogFlag& _flag )
{
     if( _flag.IsSet() )
     {
	 logFile.open( _flag.GetVal().c_str() );
#if defined(__unix__)
	  if( !logFile.is_open() )
	      throw string_exception( "Settings::SetLogStream" );
	  if( logFile.bad() )
	      throw string_exception( "Settings::SetLogStream" );
#else
	  if( !logFile.is_open() )
	      throw std::exception( "Settings::SetLogStream" );
	  if( logFile.bad() )
	      throw std::exception( "Settings::SetLogStream" );
#endif
          logStream_ = &logFile;
     }
     else
     {
          logStream_ = &std::cout;
     }
}

const ProviderInfo& Settings::ProvInfo() const
{
     return providerInfo_;
}

int Settings::IterationNum() const
{
     return iterationsNum_;
}

void Settings::SetIterationsNum( const IterationsNumFlag& _flag )
{
     iterationsNum_ = _flag.GetVal();
}

void Settings::SetCspCallStrategy( const CspCallStrategyFlag& _cspDirectCallFlag )
{
#if defined(_WIN32)
     if( _cspDirectCallFlag.GetVal() )
     {
	 csp_ = new CspDirectCall;
     }
     else
     {
	 csp_ = new CapiCspWrapper;
     }
#else
     // the only way for unix
     csp_ = new CspDirectCall;
#endif
}

