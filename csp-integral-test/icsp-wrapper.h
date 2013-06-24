#ifndef __ICSP_WRAPPER_H__
#define  __ICSP_WRAPPER_H__

#if defined(__unix__)
#ifndef __in
#define __in
#define __out
#define __inout
#endif
#endif

class ICspWrapper
{
public:
     virtual ~ICspWrapper()
     {
     }

     virtual BOOL AcquireContext(
          __out  HCRYPTPROV* phProv,
          __in   LPCTSTR pszContainer,
          __in   LPCTSTR pszProvider,
          __in   DWORD dwProvType,
          __in   DWORD dwFlags
          ) = 0;


     virtual BOOL ReleaseContext(
          __in  HCRYPTPROV hProv,
          __in  DWORD dwFlags
          ) = 0;


     virtual BOOL GetProvParam(
          __in     HCRYPTPROV hProv,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ) = 0;


     virtual BOOL SetProvParam(
          __in  HCRYPTPROV hProv,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ) = 0;


     virtual BOOL GenKey(
          __in   HCRYPTPROV hProv,
          __in   ALG_ID Algid,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ) = 0;


     virtual BOOL GetUserKey(
          __in   HCRYPTPROV hProv,
          __in   DWORD dwKeySpec,
          __out  HCRYPTKEY* phUserKey
          ) = 0;


     virtual BOOL DuplicateKey(
          __in   HCRYPTKEY hKey,
          __in   DWORD* pdwReserved,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ) = 0;


     virtual BOOL DestroyKey(
          __in  HCRYPTKEY hKey
          ) = 0;

     virtual BOOL GetKeyParam(
          __in     HCRYPTKEY hKey,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ) = 0;


     virtual BOOL SetKeyParam(
          __in  HCRYPTKEY hKey,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ) = 0;


     virtual BOOL DeriveKey(
          __in     HCRYPTPROV hProv,
          __in     ALG_ID Algid,
          __in     HCRYPTHASH hBaseData,
          __in     DWORD dwFlags,
          __inout  HCRYPTKEY* phKey
          ) = 0;


     virtual BOOL ExportKey(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTKEY hExpKey,
          __in     DWORD dwBlobType,
          __in     DWORD dwFlags,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen
          ) = 0;

     virtual BOOL ImportKey(
          __in   HCRYPTPROV hProv,
          __in   BYTE* pbData,
          __in   DWORD dwDataLen,
          __in   HCRYPTKEY hPubKey,
          __in   DWORD dwFlags,
          __out  HCRYPTKEY* phKey
          ) = 0;

     virtual BOOL GenRandom(
          __in     HCRYPTPROV hProv,
          __in     DWORD dwLen,
          __inout  BYTE* pbBuffer
          ) = 0;


     virtual BOOL Encrypt(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTHASH hHash,
          __in     BOOL Final,
          __in     DWORD dwFlags,
          __inout  BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwBufLen
          ) = 0;


     virtual BOOL Decrypt(
          __in     HCRYPTKEY hKey,
          __in     HCRYPTHASH hHash,
          __in     BOOL Final,
          __in     DWORD dwFlags,
          __inout  BYTE* pbData,
          __inout  DWORD* pdwDataLen
          ) = 0;


     virtual BOOL CreateHash(
          __in   HCRYPTPROV hProv,
          __in   ALG_ID Algid,
          __in   HCRYPTKEY hKey,
          __in   DWORD dwFlags,
          __out  HCRYPTHASH* phHash
          ) = 0;


     virtual BOOL HashData(
          __in  HCRYPTHASH hHash,
          __in  BYTE* pbData,
          __in  DWORD dwDataLen,
          __in  DWORD dwFlags
          ) = 0;


     virtual BOOL GetHashParam(
          __in     HCRYPTHASH hHash,
          __in     DWORD dwParam,
          __out    BYTE* pbData,
          __inout  DWORD* pdwDataLen,
          __in     DWORD dwFlags
          ) = 0;


     virtual BOOL SetHashParam(
          __in  HCRYPTHASH hHash,
          __in  DWORD dwParam,
          __in  const BYTE* pbData,
          __in  DWORD dwFlags
          ) = 0;


     virtual BOOL DuplicateHash(
          __in   HCRYPTHASH hHash,
          __in   DWORD* pdwReserved,
          __in   DWORD dwFlags,
          __out  HCRYPTHASH* phHash
          ) = 0;


     virtual BOOL DestroyHash(
          __in  HCRYPTHASH hHash
          ) = 0;


     virtual BOOL SignHash(
          __in     HCRYPTHASH hHash,
          __in     DWORD dwKeySpec,
          __in     LPCTSTR sDescription,
          __in     DWORD dwFlags,
          __out    BYTE* pbSignature,
          __inout  DWORD* pdwSigLen
          ) = 0;


     virtual BOOL VerifySignature(
          __in  HCRYPTHASH hHash,
          __in  BYTE* pbSignature,
          __in  DWORD dwSigLen,
          __in  HCRYPTKEY hPubKey,
          __in  LPCTSTR sDescription,
          __in  DWORD dwFlags
          ) = 0;

     virtual BOOL HashSessionKey(
          __in  HCRYPTHASH hHash,
          __in  HCRYPTKEY hKey,
          __in  DWORD dwFlags
          ) = 0;

};

#endif // #ifndef __ICSP_WRAPPER_H__