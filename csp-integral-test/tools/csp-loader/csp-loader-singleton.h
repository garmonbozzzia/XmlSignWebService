#ifndef csp_loader_singleton_h__
#define csp_loader_singleton_h__

#include "csp-func-types.h"

#if defined(__unix__)
#include <dlfcn.h>
#endif

namespace
{
	class CspLoader
	{
	public:
		CspLoader(): hLib( 0 ){}
		virtual ~CspLoader(){}

		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void* LoadFunction( LPCTSTR _name ) const = 0;
	protected:
		HMODULE hLib;
	};


	class UnixCspLoader: public CspLoader
	{
	public:
          UnixCspLoader() : libName_( "libvipnetcsp.so" )
          {
          }
		~UnixCspLoader();
		virtual void Load();
		virtual void Unload();
		virtual void* LoadFunction( LPCTSTR _name ) const;
     private:
          const std::string libName_;
	};


	class WinCspLoader: public CspLoader
	{
	public:
		~WinCspLoader();
		virtual void Load();
          virtual void Unload();
		virtual void* LoadFunction( LPCTSTR _name ) const;
	private:
          std::string GetCspDllName() const;
          std::string GetRegisteredDllName() const;
          std::string GetDllName4DebugBuild() const;
	};
} // namespace


class SingleCsp
{
public:
	static SingleCsp& Instance();
	static void Close();
	~SingleCsp();

private:
	SingleCsp& operator=( const SingleCsp& );
	SingleCsp( CspLoader* _loader );
	void LoadCpFuntions();

private:
	static SingleCsp* inst_;
	CspLoader* cspLoader_;
	
public:
	CPAcquireContext_t CPAcquireContext;
	CPGetProvParam_t CPGetProvParam;
	CPSetProvParam_t CPSetProvParam;
	CPGenRandom_t CPGenRandom;
	CPGenKey_t CPGenKey;
	CPDeriveKey_t CPDeriveKey;
	CPGetKeyParam_t CPGetKeyParam;
	CPSetKeyParam_t CPSetKeyParam;
	CPDuplicateKey_t CPDuplicateKey;
	CPDestroyKey_t CPDestroyKey;
	CPGetUserKey_t CPGetUserKey;
	CPReleaseContext_t CPReleaseContext;
	CPExportKey_t CPExportKey;
	CPImportKey_t CPImportKey;  
	CPEncrypt_t CPEncrypt;
	CPDecrypt_t CPDecrypt;
	CPCreateHash_t CPCreateHash;
	CPHashData_t CPHashData;
	CPGetHashParam_t CPGetHashParam;
	CPSetHashParam_t CPSetHashParam;
	CPDuplicateHash_t CPDuplicateHash;
	CPDestroyHash_t CPDestroyHash;
	CPSignHash_t CPSignHash;
	CPVerifySignature_t CPVerifySignature;
	//CPGetPlainKey_t CPGetPlainKey;
     CPHashSessionKey_t CPHashSessionKey;
};


#endif // csp_loader_singleton_h__
