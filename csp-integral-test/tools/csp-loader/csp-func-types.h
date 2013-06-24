#ifndef _ITCSCAPI_CSPFUNCTYPES_H
#define _ITCSCAPI_CSPFUNCTYPES_H


// typedef struct
// {
// 	DWORD   Version;
// 	FARPROC FuncVerifyImage;
// 	FARPROC FuncReturnhWnd;
// 	DWORD   dwProvType;
// 	BYTE*   pbContextInfo;
// 	DWORD   cbContextInfo;
// }
// VTableProvStruc;

typedef BOOL (WINAPI *CPAcquireContext_t)
(
 HCRYPTPROV * phProv,
 LPCTSTR pszContainer,
 DWORD dwFlags,
 VTableProvStruc* pVTable
 );

typedef BOOL (WINAPI *CPSetProvParam_t)
(
 HCRYPTPROV hProv,
 DWORD dwParam,
 const BYTE* pbData,
 DWORD dwFlags
 );

typedef BOOL (WINAPI *CPGetProvParam_t)
(
 HCRYPTPROV hProv,
 DWORD dwParam,
 BYTE* pbData,
 DWORD* pdwDataLen,
 DWORD dwFlags
 );

typedef BOOL (WINAPI *CPGenKey_t)
(
 HCRYPTPROV         hProv,  
 ALG_ID             KeyType,  
 DWORD              dwFlags,
 HCRYPTKEY    *     phKey   
 );

typedef BOOL (WINAPI *CPDeriveKey_t)
(
 HCRYPTPROV hProv,
 ALG_ID Algid,
 HCRYPTHASH hBaseData,
 DWORD dwFlags,
 HCRYPTKEY* phKey
 );

typedef BOOL (WINAPI *CPGetKeyParam_t)
( 
 HCRYPTPROV hProv,
 HCRYPTKEY hKey,
 DWORD dwParam,
 BYTE* pbData,
 DWORD* pdwDataLen,
 DWORD dwFlags
 );

typedef BOOL (WINAPI *CPSetKeyParam_t)
(
 HCRYPTPROV hProv,
 HCRYPTKEY hKey,
 DWORD dwParam,
 const BYTE* pbData,
 DWORD dwFlags
 );

typedef BOOL (WINAPI *CPDuplicateKey_t)
(
 HCRYPTPROV         hProv,  
 HCRYPTKEY          hKey,  
 DWORD        *     pdwReserved,
 DWORD              dwFlags,
 HCRYPTKEY    *     phKey   
 );

typedef BOOL (WINAPI *CPGetUserKey_t)
(                                   
 HCRYPTPROV hProv,      
 DWORD dwKeySpec,       
 HCRYPTKEY *phUserKey   
 );

typedef BOOL (WINAPI *CPReleaseContext_t)
(
 HCRYPTPROV hProv,  
 DWORD dwFlags      
 );

typedef BOOL (WINAPI *CPExportKey_t)
( 
 HCRYPTPROV hProv,
 HCRYPTKEY hKey,
 HCRYPTKEY hPubKey,
 DWORD dwBlobType,
 DWORD dwFlags,
 BYTE* pbData,
 DWORD* pdwDataLen
 );

typedef BOOL (WINAPI *CPImportKey_t)
(
 HCRYPTPROV hProv,
 const BYTE* pbData,
 DWORD dwDataLen,
 HCRYPTKEY hPubKey,
 DWORD dwFlags,
 HCRYPTKEY* phKey     
 );

typedef BOOL (WINAPI *CPDestroyKey_t)
(
 HCRYPTPROV hProv,
 HCRYPTKEY hKey
 );

typedef BOOL (WINAPI *CPGenRandom_t)
(
 HCRYPTPROV         hProv,  
 DWORD              dwLen,   
 BYTE*              pbBuffer 
 );

typedef BOOL (WINAPI *CPEncrypt_t)
(
 HCRYPTPROV hProv,
 HCRYPTKEY hKey,
 HCRYPTHASH hHash,
 BOOL Final,
 DWORD dwFlags,
 BYTE* pbData,
 DWORD* pdwDataLen,
 DWORD dwBufLen
 );

typedef BOOL (WINAPI *CPDecrypt_t)
(
 HCRYPTPROV hProv,
 HCRYPTKEY hKey,
 HCRYPTHASH hHash,
 BOOL Final,
 DWORD dwFlags,
 BYTE* pbData,
 DWORD* pdwDataLen
 );

typedef BOOL (WINAPI *CPCreateHash_t)
(
 HCRYPTPROV        hProv,    
 ALG_ID            AlgID,    
 HCRYPTKEY         hKey,      
 DWORD             dwFlags,
 HCRYPTHASH*       phHash   
 );

typedef BOOL (WINAPI *CPHashData_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash,
 const BYTE* pbData,
 DWORD dwDataLen,
 DWORD dwFlags		
 );

typedef BOOL (WINAPI *CPGetHashParam_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash,
 DWORD dwParam,
 BYTE* pbData,
 DWORD* pdwDataLen,
 DWORD dwFlags	
 );

typedef BOOL (WINAPI *CPDuplicateHash_t)
(
 HCRYPTPROV hUID,
 HCRYPTHASH hHash,
 DWORD* pdwReserved,
 DWORD dwFlags,
 HCRYPTHASH* phHash
 );

typedef BOOL (WINAPI *CPDestroyHash_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash 
 );

typedef BOOL (WINAPI *CPSetHashParam_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash,
 DWORD dwParam,
 const BYTE* pbData,
 DWORD dwFlags
 );

typedef BOOL (WINAPI *CPSignHash_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash,
 DWORD dwKeySpec,
 LPCTSTR sDescription,
 DWORD dwFlags,
 BYTE* pbSignature,
 DWORD* pdwSigLen
 );

typedef BOOL (WINAPI *CPVerifySignature_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash,
 const BYTE* pbSignature,
 DWORD dwSigLen,
 HCRYPTKEY hPubKey,
 LPCTSTR sDescription,
 DWORD dwFlags
 );


typedef BOOL (WINAPI *CPGetPlainKey_t) 
( 
 HCRYPTPROV hProv, 
 HCRYPTKEY m_hKey , 
 LPBYTE pbData, 
 LPDWORD pcbData 
 );


typedef BOOL (WINAPI *CPHashSessionKey_t)
(
 HCRYPTPROV hProv,
 HCRYPTHASH hHash,
 HCRYPTKEY hKey,
 DWORD dwFlags
 );


#endif // ifndef _ITCSCAPI_CSPFUNCTYPES_H