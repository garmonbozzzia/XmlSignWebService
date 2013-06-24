#include "stdafx.h"
#include "csp-loader-singleton.h"

#if defined(__unix__)
#define _T(x) x

void UnixCspLoader::Load()
{
    hLib = dlopen(libName_.c_str(), RTLD_LAZY );
    if( !hLib ) {
	std::string message = "UnixCspLoader fail to load ";
	message += libName_;
	throw string_exception( message.c_str() );
    }
}

void UnixCspLoader::Unload()
{
    if( !dlclose( hLib ) )
	throw string_exception( "UnixCspLoader fail to release lib handle" );
    hLib = 0;
}

void* UnixCspLoader::LoadFunction( LPCTSTR _name ) const
{
    void * functionPtr = dlsym( hLib, _name);
    if( !functionPtr ) {
	std::string message = "UnixCspLoader fail to load ";
	message += _name;
	message += " from ";
	message += libName_;
	throw string_exception( message.c_str() );
    }
    return functionPtr;
}

UnixCspLoader::~UnixCspLoader()
{
     try
     {
	     Unload();
     }
     catch( std::exception& )
     {
     }
}

#endif

#if defined(_WIN32)

void WinCspLoader::Load()
{
     hLib = LoadLibraryEx( GetCspDllName().c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH );
	if( !hLib )
     {
          std::string message = "WinCspLoader fail to load ";
          message += GetCspDllName();
          throw std::exception( message.c_str() );
     }
}

void WinCspLoader::Unload()
{
	if( !FreeLibrary( hLib ) )
		throw std::exception( "WinCspLoader fail to release lib handle" );
	hLib = 0;
}

void* WinCspLoader::LoadFunction( LPCTSTR _name ) const
{
	void* functionPtr = GetProcAddress( hLib, _name );
	if( !functionPtr )
     {
          std::string message = "WinCspLoader fail to load functions from ";
          message += GetCspDllName();
          throw std::exception( message.c_str() );
     }
	return functionPtr;
}

std::string WinCspLoader::GetRegisteredDllName() const
{

     LONG lResult = NO_ERROR;
	std::basic_string<TCHAR> regKeyPath = _T( "SOFTWARE\\" );
#ifdef _WIN64
	regKeyPath += _T( "Wow6432Node\\" );
#endif
	regKeyPath += _T( "Microsoft\\Cryptography\\Defaults\\Provider\\Infotecs Cryptographic Service Provider" );

	HKEY hKey = NULL;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, regKeyPath.c_str(), 0, KEY_READ, &hKey);
	if( lResult || !hKey)
          throw std::exception( __FUNCTION__ );

	DWORD cbData = 0;
	if( RegQueryValueEx(hKey, "Image Path", NULL, NULL, NULL, &cbData ))
		throw std::exception( __FUNCTION__ );

	std::auto_ptr<TCHAR> regStr( new TCHAR[ cbData ] );
	memset( regStr.get(), 0, cbData );
	
	if( RegQueryValueEx(hKey, "Image Path", NULL, NULL, (BYTE*)regStr.get(), &cbData ))
		throw std::exception( __FUNCTION__ );

	cbData=ExpandEnvironmentStrings(regStr.get(), NULL, 0);
	std::auto_ptr<TCHAR> dllName( new TCHAR[ cbData ] );
	
	ExpandEnvironmentStrings( regStr.get(), dllName.get(), cbData );
	return dllName.get();
}


/**
* \brief
* Для отладочных целей возвращает абсолютный путь к библиотеке криптопровайдера из каталога установки.
* Полагая, что исполняемый файл процесса находится в этом же каталоге.
* 
* \returns
* Aбсолютный путь к библиотеке криптопровайдера.
* 
* \throws <XTOOStatus>
* При невозможности получить путь к исполняемому файлу процесса.
*/
std::string WinCspLoader::GetDllName4DebugBuild() const
{
     TCHAR absolutePath[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME] = { 0 };

     if( 0 == GetModuleFileName( 0, absolutePath, _countof(absolutePath) ))
          throw std::exception( __FUNCTION__ );

     TCHAR drive[_MAX_DRIVE] = { 0 };
     TCHAR path[_MAX_DIR] = { 0 };

     _tsplitpath( absolutePath, drive, path, NULL, NULL );
     _tmakepath( absolutePath, drive, path, _T( "itccsp" ), _T( ".dll" ) ); 
     
     const DWORD actualLen = _tcslen(absolutePath) + 1;

     std::auto_ptr<TCHAR> dllAbsoluteName( new TCHAR[actualLen] );
     memcpy( dllAbsoluteName.get(), absolutePath, actualLen * sizeof(TCHAR) );

     return dllAbsoluteName.get();
}


WinCspLoader::~WinCspLoader()
{
     try
     {
          Unload();
     }
     catch( std::exception& )
     {
     }
}

std::string WinCspLoader::GetCspDllName() const
{
     bool debugBuild = false;
#ifdef _DEBUG
     debugBuild = true;
#endif // _DEBUG

     return( debugBuild? GetDllName4DebugBuild() : GetRegisteredDllName() );
}

#endif // defined (_WIN32)

SingleCsp& SingleCsp::Instance()
{
	if( !inst_ )
	{
		CspLoader* loader = 
#ifdef __unix__
			new UnixCspLoader;
#else
			new WinCspLoader;
#endif
		inst_ = new SingleCsp( loader );
	}
	return *inst_;
}

void SingleCsp::Close()
{
	if( !inst_ )
		return;

	delete inst_;
	inst_ = 0;
}

void SingleCsp::LoadCpFuntions()
{
	CPAcquireContext =  (CPAcquireContext_t) cspLoader_->LoadFunction( _T( "CPAcquireContext" ) );
	CPReleaseContext =  (CPReleaseContext_t) cspLoader_->LoadFunction( _T( "CPReleaseContext" ) );
	CPGetProvParam =    (CPGetProvParam_t)   cspLoader_->LoadFunction( _T( "CPGetProvParam" ) );
	CPSetProvParam =    (CPSetProvParam_t)   cspLoader_->LoadFunction( _T( "CPSetProvParam" ) );
	CPGetUserKey =      (CPGetUserKey_t)     cspLoader_->LoadFunction( _T( "CPGetUserKey" ) );
	CPGetKeyParam =     (CPGetKeyParam_t)    cspLoader_->LoadFunction( _T( "CPGetKeyParam" ) );
	CPSetKeyParam =     (CPSetKeyParam_t)    cspLoader_->LoadFunction( _T( "CPSetKeyParam" ) );
	CPGenKey =          (CPGenKey_t)         cspLoader_->LoadFunction( _T( "CPGenKey" ) );
	CPDeriveKey =       (CPDeriveKey_t)      cspLoader_->LoadFunction( _T(  "CPDeriveKey" ) );
	CPDuplicateKey =    (CPDuplicateKey_t)   cspLoader_->LoadFunction( _T(  "CPDuplicateKey" ) );
	CPExportKey =       (CPExportKey_t)      cspLoader_->LoadFunction( _T( "CPExportKey" ) );
	CPImportKey =       (CPImportKey_t)      cspLoader_->LoadFunction( _T( "CPImportKey" ) );
	CPGenRandom =       (CPGenRandom_t)      cspLoader_->LoadFunction( _T(  "CPGenRandom" ) );
	CPDestroyKey =      (CPDestroyKey_t)     cspLoader_->LoadFunction( _T( "CPDestroyKey" ) );
	CPEncrypt =         (CPEncrypt_t)        cspLoader_->LoadFunction( _T(  "CPEncrypt" ) );
	CPDecrypt =         (CPDecrypt_t)        cspLoader_->LoadFunction( _T(  "CPDecrypt" ) );
	CPCreateHash =      (CPCreateHash_t)     cspLoader_->LoadFunction( _T(  "CPCreateHash" ) );
	CPHashData =        (CPHashData_t)       cspLoader_->LoadFunction( _T(  "CPHashData" ) );
	CPGetHashParam =    (CPGetHashParam_t)   cspLoader_->LoadFunction( _T(  "CPGetHashParam" ) );
	CPSetHashParam =    (CPSetHashParam_t)   cspLoader_->LoadFunction( _T(  "CPSetHashParam" ) );
	CPDuplicateHash =   (CPDuplicateHash_t)  cspLoader_->LoadFunction( _T(  "CPDuplicateHash" ) );
	CPDestroyHash =     (CPDestroyHash_t)    cspLoader_->LoadFunction( _T(  "CPDestroyHash" ) );
	CPSignHash =        (CPSignHash_t)       cspLoader_->LoadFunction( _T(  "CPSignHash" ) );
	CPVerifySignature = (CPVerifySignature_t) cspLoader_->LoadFunction( _T(  "CPVerifySignature" ) );
     CPHashSessionKey =  (CPHashSessionKey_t) cspLoader_->LoadFunction( _T(  "CPHashSessionKey" ) );
#ifdef KB2_DEBUG
	//CPGetPlainKey =     (CPGetPlainKey_t)    cspLoader_->LoadFunction( _T(  "CPGetPlainKey" ) );  
#endif

     if( !CPAcquireContext
          || !CPReleaseContext
          || !CPGetProvParam
          || !CPSetProvParam
          || !CPGetUserKey
          || !CPGetKeyParam
          || !CPSetKeyParam
          || !CPGenKey
          || !CPDeriveKey
          || !CPDuplicateKey
          || !CPExportKey
          || !CPImportKey
          || !CPGenRandom
          || !CPDestroyKey
          || !CPEncrypt
          || !CPDecrypt
          || !CPCreateHash
          || !CPHashData
          || !CPGetHashParam
          || !CPSetHashParam
          || !CPDuplicateHash
          || !CPDestroyHash
          || !CPSignHash
          || !CPVerifySignature
          || !CPHashSessionKey
#ifdef KB2_DEBUG
//          || !CPGetPlainKey
#endif
          )
     {
#if defined (__unix__)
	 throw string_exception( __func__ );
#else
	 throw std::exception( __FUNCTION__ );
#endif
     }
}

SingleCsp::SingleCsp( CspLoader* _loader )
: cspLoader_( _loader )
, CPAcquireContext( 0 ) 
, CPReleaseContext( 0 ) 
, CPGetProvParam( 0 ) 
, CPSetProvParam( 0 )
, CPGetUserKey( 0 )
, CPGetKeyParam( 0 )
, CPSetKeyParam( 0 )
, CPGenKey( 0 )
, CPDeriveKey( 0 )
, CPDuplicateKey( 0 )
, CPExportKey( 0 )
, CPImportKey( 0 )
, CPGenRandom( 0 )
, CPDestroyKey( 0 )
, CPEncrypt( 0 )
, CPDecrypt( 0 )
, CPCreateHash( 0 )
, CPHashData( 0 )
, CPGetHashParam( 0 )
, CPSetHashParam( 0 )
, CPDuplicateHash( 0 )
, CPDestroyHash( 0 )
, CPSignHash( 0 )
, CPVerifySignature( 0 )
, CPHashSessionKey( 0 )
{
	if( !cspLoader_ )
#if defined (__unix__)
	    throw string_exception( __func__ );
#else
	    throw std::exception( __FUNCTION__ );
#endif
	cspLoader_->Load();
	LoadCpFuntions();
}

SingleCsp::~SingleCsp()
{
	delete cspLoader_;
}

SingleCsp* SingleCsp::inst_ = 0;