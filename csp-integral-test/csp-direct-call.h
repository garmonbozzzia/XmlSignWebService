#ifndef __CSP_DIRECT_CALL__
#define __CSP_DIRECT_CALL__

#include "icsp-wrapper.h"
#include "tools/csp-loader/csp-loader-singleton.h"

#if defined(__unix__)
#ifndef __in
#define __in
#define __out
#define __inout
#endif
#endif

class CspDirectCall :
     public ICspWrapper
{
     struct Handle{
          HCRYPTPROV prov;
     };
     struct KeyHandle: public Handle{
          HCRYPTKEY handle;
     };

     struct HashHandle: public Handle{
          HCRYPTHASH handle;
     };

     typedef std::list<Handle*> Handles;

public:
     CspDirectCall(){}
     ~CspDirectCall(){}

     virtual BOOL AcquireContext(
          __out  HCRYPTPROV* phProv,
          __in   LPCTSTR pszContainer,
          __in   LPCTSTR pszProvider,
          __in   DWORD dwProvType,
          __in   DWORD dwFlags
          ){
               VTableProvStruc VTable = { 0 };
               VTable.Version = 1;
               
               return SingleCsp::Instance().CPAcquireContext( phProv, pszContainer, dwFlags, &VTable );
               
     }


     virtual BOOL ReleaseContext(
          __in  HCRYPTPROV hProv,
          __in  DWORD dwFlags
          ){
               return SingleCsp::Instance().CPReleaseContext( hProv, dwFlags );
     }


     virtual BOOL GetProvParam(
          __in     HCRYPTPROV hProv,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ){
               return SingleCsp::Instance().CPGetProvParam( hProv, dwParam, pbData, pdwDataLen, dwFlags );
     }


     virtual BOOL SetProvParam(
          __in  HCRYPTPROV hProv,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ){
               return SingleCsp::Instance().CPSetProvParam( hProv, dwParam, pbData, dwFlags );
     }


     virtual BOOL GenKey(
          __in   HCRYPTPROV hProv,
          __in   ALG_ID Algid,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ){
               KeyHandle* key = new KeyHandle;
               key->prov = hProv;

               BOOL res = SingleCsp::Instance().CPGenKey( key->prov, Algid, dwFlags, &key->handle );
               if( res )
               {
                    handles_.push_back( key );
                    *phKey = (HCRYPTKEY)key;
               }
               return res;
     }


     virtual BOOL GetUserKey(
          __in   HCRYPTPROV hProv,
          __in   DWORD dwKeySpec,
          __out  HCRYPTKEY* phUserKey
          ){
               KeyHandle* key = new KeyHandle;
               key->prov = hProv;

               BOOL res = SingleCsp::Instance().CPGetUserKey( key->prov, dwKeySpec, &key->handle );
               if( res )
               {
                    handles_.push_back( key );
                    *phUserKey = (HCRYPTKEY)key;
               }
               return res;
     }


     virtual BOOL DuplicateKey(
          __in   HCRYPTKEY hKey,
          __in   DWORD* pdwReserved,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               KeyHandle* dublicate = new KeyHandle;
               dublicate->prov = key->prov;

               BOOL res = SingleCsp::Instance().CPDuplicateKey( key->prov, key->handle, pdwReserved, dwFlags, &dublicate->handle );
               if( res )
               {
                    handles_.push_back( dublicate );
                    *phKey = (HCRYPTKEY)dublicate;
               }
               return res;
     }


     virtual BOOL DestroyKey(
          __in  HCRYPTKEY hKey
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               BOOL res = SingleCsp::Instance().CPDestroyKey( key->prov, key->handle );
               if( res )
               {
                    Handles::iterator i = std::find( handles_.begin(), handles_.end(), key );
                    if( i != handles_.end() )
                         handles_.erase( i );
               }
               return res;
     }

     virtual BOOL GetKeyParam(
          __in     HCRYPTKEY hKey,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               return SingleCsp::Instance().CPGetKeyParam( key->prov, key->handle, dwParam, pbData, pdwDataLen, dwFlags );
     }


     virtual BOOL SetKeyParam(
          __in  HCRYPTKEY hKey,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               return SingleCsp::Instance().CPSetKeyParam( key->prov, key->handle, dwParam, pbData, dwFlags );
     }


     virtual BOOL DeriveKey(
          __in     HCRYPTPROV hProv,
          __in     ALG_ID Algid,
          __in     HCRYPTHASH hBaseData,
          __in     DWORD dwFlags,
          __inout  HCRYPTKEY* phKey
          ){
               KeyHandle* key = new KeyHandle;
               key->prov = hProv;

               BOOL res = SingleCsp::Instance().CPDeriveKey( key->prov, Algid, hBaseData, dwFlags, &key->handle );
               if( res )
               {
                    handles_.push_back( key );
                    *phKey = (HCRYPTKEY)key;
               }
               return res;
     }


     virtual BOOL ExportKey(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTKEY hExpKey,
          __in     DWORD dwBlobType,
          __in     DWORD dwFlags,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               KeyHandle* expKey =  (KeyHandle*)hExpKey;
	return SingleCsp::Instance().CPExportKey(key->prov,
						 key->handle,
						 expKey ? expKey->handle : 0,
						 dwBlobType,
						 dwFlags,
						 pbData,
						 pdwDataLen);
    }

     virtual BOOL ImportKey(
          __in   HCRYPTPROV hProv,
          __in   BYTE* pbData,
          __in   DWORD dwDataLen,
          __in   HCRYPTKEY hPubKey,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ){
               KeyHandle* key = new KeyHandle;
               key->prov = hProv;
               KeyHandle* pubKey = (KeyHandle*)hPubKey;

	BOOL res = SingleCsp::Instance().CPImportKey(hProv,
						     pbData,
						     dwDataLen,
						     pubKey ? pubKey->handle : 0,
						     dwFlags,
						     &key->handle);
	if( res )
	{
	    handles_.push_back( key );
	    *phKey = (HCRYPTKEY)key;
	}
	return res;
    }

     virtual BOOL GenRandom(
          __in     HCRYPTPROV hProv,
          __in     DWORD dwLen,
          __inout  BYTE* pbBuffer
          ){
               return SingleCsp::Instance().CPGenRandom( hProv, dwLen, pbBuffer );
     }


     virtual BOOL Encrypt(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTHASH hHash,
          __in     BOOL Final,
          __in     DWORD dwFlags,
          __inout  BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwBufLen
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               HashHandle* hash = (HashHandle*)hHash;

	return SingleCsp::Instance().CPEncrypt(key->prov,
					       key->handle,
					       hash ? hash->handle : 0,
					       Final,
					       dwFlags,
					       pbData,
					       pdwDataLen,
					       dwBufLen);
    }


     virtual BOOL Decrypt(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTHASH hHash,
          __in     BOOL Final,
          __in     DWORD dwFlags,
          __inout  BYTE* pbData,
          __inout  DWORD* pdwDataLen
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               HashHandle* hash = (HashHandle*)hHash;

	return SingleCsp::Instance().CPDecrypt(key->prov,
					       key->handle,
					       hash ? hash->handle : 0,
					       Final,
					       dwFlags,
					       pbData,
					       pdwDataLen);
    }


    virtual BOOL CreateHash(
	__in   HCRYPTPROV hProv,
	__in   ALG_ID Algid,
	__in   HCRYPTKEY hKey,
	__in   DWORD dwFlags,
	__out  HCRYPTHASH* phHash){
	 
	HashHandle* hash = new HashHandle;
	hash->prov = hProv;
	KeyHandle* key =  (KeyHandle*)hKey;
	BOOL res = SingleCsp::Instance().CPCreateHash(hash->prov, Algid, key ? key->handle : 0, dwFlags, &hash->handle );
	if( res )
	{
	    handles_.push_back( hash );
	    *phHash = (HCRYPTHASH)hash;
	}
	return res;
    }


     virtual BOOL HashData(
          __in  HCRYPTHASH hHash,
          __in  BYTE* pbData,
          __in  DWORD dwDataLen,
          __in  DWORD dwFlags
          ){
               HashHandle* hash = (HashHandle*)hHash;
               return SingleCsp::Instance().CPHashData( hash->prov, hash->handle, pbData, dwDataLen, dwFlags );
     }


     virtual BOOL GetHashParam(
          __in     HCRYPTHASH hHash,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ){
               HashHandle* hash = (HashHandle*)hHash;
               return SingleCsp::Instance().CPGetHashParam( hash->prov, hash->handle, dwParam, pbData, pdwDataLen, dwFlags );
     }


     virtual BOOL SetHashParam(
          __in  HCRYPTHASH hHash,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ){
               HashHandle* hash = (HashHandle*)hHash;
               return SingleCsp::Instance().CPSetHashParam( hash->prov, hash->handle, dwParam, pbData, dwFlags );
     }


     virtual BOOL DuplicateHash(
          __in   HCRYPTHASH hHash,
          __in   DWORD* pdwReserved,
          __in   DWORD dwFlags,
          __out  HCRYPTHASH* phHash
          ){
               HashHandle* hash = (HashHandle*)hHash;
               HashHandle* dublicate = new HashHandle;
               dublicate->prov = hash->prov;
               BOOL res = SingleCsp::Instance().CPDuplicateHash( hash->prov, hash->handle, pdwReserved, dwFlags, &dublicate->handle );
               if( res )
               {
                    handles_.push_back( dublicate );
                    *phHash = (HCRYPTHASH)dublicate;
               }
               return res;
     }


     virtual BOOL DestroyHash(
          __in  HCRYPTHASH hHash
          ){
               HashHandle* hash = (HashHandle*)hHash;
               BOOL res = SingleCsp::Instance().CPDestroyHash( hash->prov, hash->handle );
               if( res )
               {
                    Handles::iterator i = std::find( handles_.begin(), handles_.end(), hash );
                    if( i != handles_.end() )
                         handles_.erase( i );
               }
               return res;
     }


    virtual BOOL SignHash(
	__in     HCRYPTHASH hHash,
	__in     DWORD dwKeySpec,
	__in     LPCTSTR sDescription,
	__in     DWORD dwFlags,
	__out    BYTE* pbSignature,
	__inout  DWORD* pdwSigLen
	){
	HashHandle* hash = (HashHandle*)hHash;
	return SingleCsp::Instance().CPSignHash(hash->prov,
						hash->handle,
						dwKeySpec,
						sDescription,
						dwFlags,
						pbSignature,
						pdwSigLen );
    }


    virtual BOOL VerifySignature(
	__in  HCRYPTHASH hHash,
	__in  BYTE* pbSignature,
	__in  DWORD dwSigLen,
	__in  HCRYPTKEY hPubKey,
	__in  LPCTSTR sDescription,
	__in  DWORD dwFlags)
    {
	HashHandle* hash = (HashHandle*)hHash;
	KeyHandle* pubKey = (KeyHandle*)hPubKey;
	return SingleCsp::Instance().CPVerifySignature(hash->prov,
						       hash->handle,
						       pbSignature,
						       dwSigLen,
						       pubKey ? pubKey->handle : 0,
						       sDescription,
						       dwFlags);
    }

     virtual BOOL HashSessionKey(
          __in  HCRYPTHASH hHash,
          __in  HCRYPTKEY hKey,
          __in  DWORD dwFlags
          ){
               KeyHandle* key =  (KeyHandle*)hKey;
               HashHandle* hash = (HashHandle*)hHash;

               return SingleCsp::Instance().CPHashSessionKey( hash->prov, hash->handle, key->handle, dwFlags );
     }

     private:
          Handles handles_;
};

#endif

