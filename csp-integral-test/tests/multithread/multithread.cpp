/// @file
/// @brief Файл содержит определение методов класса, тестирующего работу в многопоточном режиме.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "multithread.h"

#include "../capi-1/key-generation.h"
#include "../capi-1/encryption.h"
#include "../capi-1/exportation.h"
#include "../capi-1/signing.h"
#include "../capi-1/diffie-hellman.h"
#include "../integral-test.h"

#include <process.h>


using namespace multithread_test_internal;


unsigned WINAPI ThreadFunction( LPVOID pParam )
{
	ThreadInfo* info = static_cast<ThreadInfo*>(pParam);
	
	ThreadSettingsBuilder builder( info );
	IntegralTest integral( *builder.GetSettings() );
	integral.AddTest( new KeyGeneration );
	integral.AddTest( new Encryption );
	integral.AddTest( new Exportation );
	integral.AddTest( new Signing );
	integral.AddTest( new DiffieHellman );

	integral.Run();

	return 0;
}


void Multithread::Run()
{
	GetSettings()->LogStream() << "\nMultithread::Run()\n";
	GetSettings()->LogStream().flush();

	std::vector<ThreadInfo*> threadsInfo;

	try
	{
		static const int threadNum = 10;
		
		for( int i = 0; i < threadNum; ++i )
		{
			ThreadInfo* info = new ThreadInfo;
			info->threadNum = i;
			info->parentSettings = GetSettings();

			info->handle = ( HANDLE )_beginthreadex( 0, 0, &ThreadFunction, 
				info, CREATE_SUSPENDED, 0 );

			threadsInfo.push_back( info );
		}

		std::vector<HANDLE> handles;
		for( std::vector<ThreadInfo*>::iterator i = threadsInfo.begin(); i != threadsInfo.end(); ++i )
		{
			GetSettings()->LogStream() << "\nStarting thread " << (*i)->threadNum <<"..";
			GetSettings()->LogStream().flush();

			ResumeThread( (*i)->handle );
			handles.push_back( (*i)->handle );
		}

		WaitForMultipleObjects ( handles.size(), &handles[0], TRUE, INFINITE );
		
		GetSettings()->LogStream() <<"\nSuccess\n";
		GetSettings()->LogStream().flush();
	}
	catch( csp_exception& e )
	{
		GetSettings()->LogStream() << e.what() <<"\n";
		GetSettings()->LogStream().flush();
	}
	
	for( std::vector<ThreadInfo*>::iterator j = threadsInfo.begin(); j != threadsInfo.end(); ++j )
	{
		CloseHandle ( (*j)->handle );
		delete *j; 
	}
}


namespace multithread_test_internal
{

	ThreadSettingsBuilder::ThreadSettingsBuilder( ThreadInfo* info )
		: info_( info )
		, settings_( 0 )
		, containerName_( ThreadName() + _T( ".cont" ) )
		, logName_( ThreadName() + _T( ".log" ) )
	{
		TCHAR* argv[] = { 
			const_cast<TCHAR*>(info_->parentSettings->MessageFile()), 
			const_cast<TCHAR*>(_T( "-l" )), 
			const_cast<TCHAR*>( logName_.c_str() ),
			const_cast<TCHAR*>( _T( "-c" )),
			const_cast<TCHAR*>( containerName_.c_str() ),
		};
		int argc = _countof( argv );

		CmdLineInput cmd( argc, argv );
		settings_ = new Settings( cmd, info_->parentSettings->ProvInfo() );
	}

	ThreadSettingsBuilder::~ThreadSettingsBuilder()
	{
		delete settings_;
	}

	tstring ThreadSettingsBuilder::ThreadName() const
	{
		std::basic_string<TCHAR> threadName = _T( "thread_" );
		TCHAR buf[ 2 ] = { 0 }; 
		threadName += _itot( info_->threadNum, buf, 10 );
		return threadName;
	}
}
