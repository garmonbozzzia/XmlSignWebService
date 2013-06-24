#ifndef CAPI_CSP_WRAPPER_H__
#define CAPI_CSP_WRAPPER_H__

#if defined(_WIN32)
#include <windows.h>
#include <WinCrypt.h>
#endif

#if defined(__unix__)
#ifndef __in
#define __in
#define __out
#define __inout
#endif
#endif

#include "icsp-wrapper.h"

class CapiCspWrapper :
     public ICspWrapper
{
public:
     CapiCspWrapper(){}
     ~CapiCspWrapper(){}

     virtual BOOL AcquireContext(
          __out  HCRYPTPROV* phProv,
          __in   LPCTSTR pszContainer,
          __in   LPCTSTR pszProvider,
          __in   DWORD dwProvType,
          __in   DWORD dwFlags
          ){
               return CryptAcquireContext( phProv, pszContainer, pszProvider, dwProvType, dwFlags );
     }


     virtual BOOL ReleaseContext(
          __in  HCRYPTPROV hProv,
          __in  DWORD dwFlags
          ){
               return CryptReleaseContext( hProv, dwFlags );
     }


     virtual BOOL GetProvParam(
          __in     HCRYPTPROV hProv,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ){
               return CryptGetProvParam( hProv, dwParam, pbData, pdwDataLen, dwFlags );
     }


     virtual BOOL SetProvParam(
          __in  HCRYPTPROV hProv,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ){
               return CryptSetProvParam( hProv, dwParam, pbData, dwFlags );
     }


     virtual BOOL GenKey(
          __in   HCRYPTPROV hProv,
          __in   ALG_ID Algid,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ){
               return CryptGenKey( hProv, Algid, dwFlags, phKey ); 
     }


     virtual BOOL GetUserKey(
          __in   HCRYPTPROV hProv,
          __in   DWORD dwKeySpec,
          __out  HCRYPTKEY* phUserKey
          ){
               return CryptGetUserKey( hProv, dwKeySpec, phUserKey );
     }


     virtual BOOL DuplicateKey(
          __in   HCRYPTKEY hKey,
          __in   DWORD* pdwReserved,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ){
               return CryptDuplicateKey( hKey, pdwReserved, dwFlags, phKey );
     }


     virtual BOOL DestroyKey(
          __in  HCRYPTKEY hKey
          ){
               return CryptDestroyKey( hKey );
     }

     virtual BOOL GetKeyParam(
          __in     HCRYPTKEY hKey,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ){
               return CryptGetKeyParam( hKey, dwParam, pbData, pdwDataLen, dwFlags );
     }


     virtual BOOL SetKeyParam(
          __in  HCRYPTKEY hKey,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ){
               return CryptSetKeyParam( hKey, dwParam, pbData, dwFlags );
     }


     virtual BOOL DeriveKey(
          __in     HCRYPTPROV hProv,
          __in     ALG_ID Algid,
          __in     HCRYPTHASH hBaseData,
          __in     DWORD dwFlags,
          __inout  HCRYPTKEY* phKey
          ){
               return CryptDeriveKey( hProv, Algid, hBaseData, dwFlags, phKey );
     }


     virtual BOOL ExportKey(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTKEY hExpKey,
          __in     DWORD dwBlobType,
          __in     DWORD dwFlags,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen
          ){
               return CryptExportKey( hKey, hExpKey, dwBlobType, dwFlags, pbData, pdwDataLen );
     }

     virtual BOOL ImportKey(
          __in   HCRYPTPROV hProv,
          __in   BYTE* pbData,
          __in   DWORD dwDataLen,
          __in   HCRYPTKEY hPubKey,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ){
               return CryptImportKey( hProv, pbData, dwDataLen, hPubKey, dwFlags, phKey );
     }

     virtual BOOL GenRandom(
          __in     HCRYPTPROV hProv,
          __in     DWORD dwLen,
          __inout  BYTE* pbBuffer
          ){
               return CryptGenRandom( hProv, dwLen, pbBuffer );
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
               return CryptEncrypt( hKey, hHash, Final, dwFlags, pbData, pdwDataLen, dwBufLen );
     }


     virtual BOOL Decrypt(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTHASH hHash,
          __in     BOOL Final,
          __in     DWORD dwFlags,
          __inout  BYTE* pbData,
          __inout  DWORD* pdwDataLen
          ){
               return CryptDecrypt( hKey, hHash, Final, dwFlags, pbData, pdwDataLen );
     }


     virtual BOOL CreateHash(
          __in   HCRYPTPROV hProv,
          __in   ALG_ID Algid,
          __in   HCRYPTKEY hKey,
          __in   DWORD dwFlags,
          __out  HCRYPTHASH* phHash
          ){
               return CryptCreateHash( hProv, Algid, hKey, dwFlags, phHash );
     }


     virtual BOOL HashData(
          __in  HCRYPTHASH hHash,
          __in  BYTE* pbData,
          __in  DWORD dwDataLen,
          __in  DWORD dwFlags
          ){
               return CryptHashData( hHash, pbData, dwDataLen, dwFlags );
     }


     virtual BOOL GetHashParam(
          __in     HCRYPTHASH hHash,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ){
               return CryptGetHashParam( hHash, dwParam, pbData, pdwDataLen, dwFlags );
     }


     virtual BOOL SetHashParam(
          __in  HCRYPTHASH hHash,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ){
               return CryptSetHashParam( hHash, dwParam, pbData, dwFlags );
     }


     virtual BOOL DuplicateHash(
          __in   HCRYPTHASH hHash,
          __in   DWORD* pdwReserved,
          __in   DWORD dwFlags,
          __out  HCRYPTHASH* phHash
          ){
               return CryptDuplicateHash( hHash, pdwReserved, dwFlags, phHash );
     }


     virtual BOOL DestroyHash(
          __in  HCRYPTHASH hHash
          ){
               return CryptDestroyHash( hHash );
     }


     virtual BOOL SignHash(
          __in     HCRYPTHASH hHash,
          __in     DWORD dwKeySpec,
          __in     LPCTSTR sDescription,
          __in     DWORD dwFlags,
          __out    BYTE* pbSignature,
          __inout  DWORD* pdwSigLen
          ){
               return CryptSignHash( hHash, dwKeySpec, sDescription, dwFlags, pbSignature, pdwSigLen );
     }


     virtual BOOL VerifySignature(
          __in  HCRYPTHASH hHash,
          __in  BYTE* pbSignature,
          __in  DWORD dwSigLen,
          __in  HCRYPTKEY hPubKey,
          __in  LPCTSTR sDescription,
          __in  DWORD dwFlags
          ){
               return CryptVerifySignature( hHash, pbSignature, dwSigLen, hPubKey, sDescription, dwFlags );
     }

     virtual BOOL HashSessionKey(
          __in  HCRYPTHASH hHash,
          __in  HCRYPTKEY hKey,
          __in  DWORD dwFlags
          ){
               return CryptHashSessionKey( hHash, hKey, dwFlags );
     }
};
#endif // CAPI_CSP_WRAPPER_H__
