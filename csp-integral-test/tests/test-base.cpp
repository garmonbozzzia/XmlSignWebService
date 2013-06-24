/// @file
/// @brief Файл содержит определение методов базового тестового класса.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "test-base.h"
#include <assert.h>


TestBase::TestBase()
: settings_( 0 )
{
}


void TestBase::SetSettings( const Settings* _settings )
{
	assert( _settings );
	settings_ = _settings;
}


const Settings* TestBase::GetSettings() const
{
	return settings_;
}

void TestBase::CreateContainerIfNotExists( HCRYPTPROV& _prov, bool _withGui /*= false */ ) const
{
	HCRYPTPROV prov = 0;
     DWORD silentFlag = _withGui? 0 : CRYPT_SILENT;

     /// Пытаемся открыть контекст криптопровайдера
	BOOL ret = GetSettings()->csp()->AcquireContext( &_prov, 
		GetSettings()->Container(), 
		GetSettings()->ProvInfo().Name(),
		GetSettings()->ProvInfo().Type(),
		silentFlag );

	if( !ret 
		&& ( GetLastError() == NTE_BAD_KEYSET 
		|| GetLastError() == NTE_KEYSET_NOT_DEF
          || GetLastError() == S_OK ))
	{
		GetSettings()->LogStream() <<"Creating container <" <<GetSettings()->Container() <<">..\n";
		GetSettings()->LogStream().flush();

          /// Если ключевой контейнер, на который ссылается контекст, не существует, то создаем его.
		ret = GetSettings()->csp()->AcquireContext( &_prov, 
			GetSettings()->Container(), 
			GetSettings()->ProvInfo().Name(),
			GetSettings()->ProvInfo().Type(),
			CRYPT_NEWKEYSET | silentFlag );
	}
	if( !ret )
		throw csp_exception( "CryptAcquireContext", GetLastError() );
}

void TestBase::CreateKeyIfNotExists(HCRYPTPROV _prov, ALG_ID _alg, HCRYPTKEY& _key ) const
{
	GetSettings()->LogStream() <<"Getting key with algorithm id=" <<std::hex <<_alg;
	GetSettings()->LogStream() <<" from container <" <<GetSettings()->Container() <<">..\n";
	GetSettings()->LogStream().flush();

     /// Пытаемся получить ключ из контейнера, на который ссылается контекст криптопровайдера.
	if( !GetSettings()->csp()->GetUserKey( _prov, _alg, &_key ) )
	{
		if( GetLastError() == NTE_NO_KEY )
		{
			GetSettings()->LogStream() <<"Key doesn't exist. Creating..\n";
			GetSettings()->LogStream().flush();

               /// Если в контейнере нет ключа - создаем.
			if( !GetSettings()->csp()->GenKey( _prov, _alg, 0, &_key ) )
               {
                    if( GetLastError() == NTE_SILENT_CONTEXT ){
                         /// Если в неинтерактивном режиме создать ключ не получается, переоткроем контекст в интерактивном режиме.
                         GetSettings()->csp()->ReleaseContext( _prov, 0 );
                         CreateContainerIfNotExists( _prov, true );
                         /// Создаем ключ в интерактивном режиме.
                         if( !GetSettings()->csp()->GenKey( _prov, _alg, 0, &_key ) )
                              throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );
                    }
                    else{
                         throw csp_exception( "CryptGenKey", GetLastError() );
                    }
               }
		}
		else
			throw csp_exception( "GetSettings()->csp()->GetUserKey", GetLastError() );
	}
}


void TestBase::GetMessage( std::vector<BYTE>& _buffer ) const
{
	GetSettings()->LogStream() <<"Getting message from file <" <<GetSettings()->MessageFile() <<">..\n";
	GetSettings()->LogStream().flush();

	std::ifstream messageFile( GetSettings()->MessageFile() );
	if( messageFile.bad() )
	{
		std::string errMessage = "Can't open message file: ";
		errMessage += GetSettings()->MessageFile();
		throw std::bad_exception( errMessage.c_str() );
	}
     messageFile.seekg( 0, std::ios_base::end );
     _buffer.resize( messageFile.tellg() );
     messageFile.seekg( 0, std::ios_base::beg );
     messageFile.read( reinterpret_cast<char*>(&_buffer[0]), _buffer.size() );
     if( _buffer.empty() )
		throw std::bad_exception( "Message file is not exist or empty" );
}

void TestBase::SafeRun()
{
	try
	{ 
		Run(); 
	}
	catch( std::exception& e )
	{
		GetSettings()->LogStream() <<"Error: " <<e.what() <<"\n";
	}
}


