/// @file
/// @brief Файл содержит определение методов класса, тестирующего стрессовом режиме.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "stress.h"

#include "../../tools/certificate-search.h"
#include "../capi-1/key-generation.h"
#include "../capi-1/encryption.h"
#include "../capi-1/exportation.h"
#include "../capi-1/signing.h"
#include "../capi-1/diffie-hellman.h"



void Stress::Run()
{
     GetSettings()->LogStream() << "\nStress::Run()\n";
     GetSettings()->LogStream() << std::ios_base::dec;
     GetSettings()->LogStream() << "\niterations num = " << GetSettings()->IterationNum();
     GetSettings()->LogStream().flush();

     try
     {
          diffieHellman();    
          pkcs7();
          pkcs7Sign();
          GetSettings()->LogStream() <<"\nSuccess\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() << e.what() <<"\n";
          GetSettings()->LogStream().flush();
     }
}

void Stress::diffieHellman()
{
     GetSettings()->LogStream() << "\n\nStress::diffieHellman()\n";
     GetSettings()->LogStream().flush();
     std::vector<BYTE> publicKeyBlob;
     generatePublicKey( publicKeyBlob );
     std::vector<BYTE> data;
     getTestPlainText( data );

     HCRYPTPROV dumpProv = 0;
     CreateContainerIfNotExists( dumpProv );
     CryptSetProvParam( dumpProv, PP_SIGNATURE_PIN, (LPBYTE)"111111", 0);
     HCRYPTKEY dumpKey = 0;
     CreateKeyIfNotExists( dumpProv, AT_KEYEXCHANGE, dumpKey );

     int i = 0;
     try
     {
          GetSettings()->LogStream() << "Stress test progress:";
          GetSettings()->LogStream().flush();
          for( i = 0; i < GetSettings()->IterationNum(); ++i )
          {
               diffieHellmanOneTestIteration( publicKeyBlob, data );
               progress( i );
          }
          GetSettings()->LogStream() << "ok";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& )
     {
          if( i < GetSettings()->IterationNum() )
          {
               GetSettings()->LogStream() <<"Error: stress test fail on " <<i <<"-th iteration \n";
               GetSettings()->LogStream().flush();
          }
          throw;
     }
}

void Stress::generatePublicKey( std::vector<BYTE>& _outBlob ) const
{
     _outBlob.clear();

     GetSettings()->LogStream() << "Acquiring virtual provider context 1..\n";
     GetSettings()->LogStream().flush();
     HCRYPTPROV prov1 = 0;
     if( !CryptAcquireContext( &prov1, 
          0, 
          GetSettings()->ProvInfo().Name(),
          GetSettings()->ProvInfo().Type(),
          CRYPT_VERIFYCONTEXT ) )
     {
          throw csp_exception( "CryptAcquireContext", GetLastError() );
     }

     GetSettings()->LogStream() <<"Creating key pair 1..\n";
     GetSettings()->LogStream().flush();
     HCRYPTKEY keypair1 = 0;
     if( !CryptGenKey( prov1, AT_KEYEXCHANGE, 0, &keypair1 ) )
          throw csp_exception( "CryptGenKey", GetLastError() );

     GetSettings()->LogStream() << "Getting size of PUBLICKEYBLOB..\n";
     GetSettings()->LogStream().flush();
     DWORD blobSize = 0;
     if( !CryptExportKey( keypair1, 0, PUBLICKEYBLOB, 0, 0, &blobSize ) )
          throw csp_exception( "CryptExportKey", GetLastError() );

     GetSettings()->LogStream() << "Exporting public key 1 from provider context 1..\n";
     GetSettings()->LogStream().flush();
     std::vector<BYTE> publicBlob1( blobSize );
     if( !CryptExportKey( keypair1, 0, PUBLICKEYBLOB, 0, &publicBlob1[0], &blobSize ) )
          throw csp_exception( "CryptExportKey", GetLastError() );

     _outBlob = publicBlob1;
}

void Stress::diffieHellmanOneTestIteration( 
     const std::vector<BYTE>& _inPublicKeyBlob, 
     const std::vector<BYTE>& _data 
     ) const
{
     HCRYPTPROV prov = 0;
     if( !CryptAcquireContext( &prov, 
          GetSettings()->Container(), 
          GetSettings()->ProvInfo().Name(),
          GetSettings()->ProvInfo().Type(),
          CRYPT_SILENT ))
     {
          throw csp_exception( __FUNCTION__ "CryptAcquireContext", GetLastError() );
     }
     

     if( !CryptSetProvParam( prov, PP_SIGNATURE_PIN, (LPBYTE)"111111", 0 ))
          throw csp_exception( __FUNCTION__ "CryptSetProvParam", GetLastError() );

     HCRYPTKEY  hSessionKey = 0;
     if ( !CryptGenKey(prov,GetSettings()->ProvInfo().SessionKeyAlgId(),CRYPT_EXPORTABLE,&hSessionKey) )
          throw csp_exception( __FUNCTION__, GetLastError() );

     HCRYPTKEY senderKey = 0;
     if( !CryptGetUserKey( prov, AT_KEYEXCHANGE, &senderKey ) )
          throw csp_exception( __FUNCTION__ "CryptGetUserKey", GetLastError() );

     //получение ключа обмена импортом секретного ключа отправителя 
     //на открытый ключ получателя (схема Диффи-Хеллмана)
     HCRYPTKEY exchKey = 0;
     if ( !CryptImportKey( prov, &_inPublicKeyBlob[0], _inPublicKeyBlob.size(), senderKey, 0, &exchKey ) )
          throw csp_exception( "CryptImportKey", GetLastError() );
     // дискриптор ключа сохраняем в объекте для утилизации

     // ДЛЯ ИНФОТЕКС НАЧАЛО
     // устанавливаем алгоритм экспорта блоба
     ALG_ID aidExportAlg = CALG_SIMPLE_EXPORT;
     if ( !CryptSetKeyParam( exchKey, KP_ALGID, (LPBYTE)(&aidExportAlg), 0) )
          throw csp_exception( "CryptSetKeyParam", GetLastError() );
     // ДЛЯ ИНФОТЕКС КОНЕЦ
     DWORD cbSessionKey = 0;
     // шифрование ключа обмена на сессионном ключе - собственно экспорт блоба сессионного ключа для передачи получателю
     if ( !CryptExportKey(hSessionKey, exchKey, SIMPLEBLOB, 0, NULL, &cbSessionKey) )
          throw csp_exception( "CryptExportKey", GetLastError() );
     // получаем область памяти для ключа
     std::vector<BYTE> sesKeyBlob( cbSessionKey );

     // шифрование сессионногоключа
     if ( !CryptExportKey(hSessionKey, exchKey, SIMPLEBLOB, 0, &sesKeyBlob[0], &cbSessionKey) )
          throw csp_exception( "CryptExportKey", GetLastError() );
     // определение вектора инициализации сессионного ключа - размер вектора
     DWORD cbIV = 0;
     if ( !CryptGetKeyParam(hSessionKey,KP_IV,NULL,&cbIV,0) )
          throw csp_exception( "CryptGetKeyParam", GetLastError() );
     // резервирование памяти для вектора инициализации
     std::vector<BYTE> iv( cbIV );

     // получаем вектор инициализации сессионного ключа
     if ( !CryptGetKeyParam(hSessionKey,KP_IV,&iv[0], &cbIV,0) )
          throw csp_exception( "CryptGetKeyParam", GetLastError() );
     //шифрование данных на сессионном ключе

     DWORD dwEncryptedLen = _data.size();
     if ( !CryptEncrypt( hSessionKey, 0, TRUE, 0, 0, &dwEncryptedLen,_data.size() ) )
          throw csp_exception( "CryptEncrypt", GetLastError() );

     std::vector<BYTE> encrypted( dwEncryptedLen );
     std::copy( _data.begin(), _data.end(), encrypted.begin() );
     dwEncryptedLen = _data.size();

     if ( !CryptEncrypt(hSessionKey,0,TRUE,0,&encrypted[0], &dwEncryptedLen,encrypted.size() ) )
          throw csp_exception( "CryptEncrypt", GetLastError() );
}

void Stress::getTestPlainText( std::vector<BYTE>& _out ) const
{
     _out.clear();

     HCRYPTPROV prov = 0;
     if( !CryptAcquireContext( &prov, 
          0, 
          GetSettings()->ProvInfo().Name(),
          GetSettings()->ProvInfo().Type(),
          CRYPT_VERIFYCONTEXT ) )
     {
          throw csp_exception( "CryptAcquireContext", GetLastError() );
     }
     static const int TEST_DATA_SIZE = 1000;
     _out.resize( TEST_DATA_SIZE );
     if( !CryptGenRandom( prov, _out.size(), &_out[0] ))
          throw csp_exception( "CryptGenRandom", GetLastError() );
}

void Stress::pkcs7() const
{
     GetSettings()->LogStream() << "\n\nStress::pkcs7\n";
     GetSettings()->LogStream().flush();

     std::vector<BYTE> data;
     getTestPlainText( data );

     GetSettings()->LogStream() <<"Searching for certificate..\n";
     GetSettings()->LogStream().flush();

     CertificateGuiSearch certificateSearch;
     certificateSearch.FindContext();

     int i = 0;
     try
     {
          GetSettings()->LogStream() << "Stress test progress:";
          GetSettings()->LogStream().flush();
          for( i = 0; i < GetSettings()->IterationNum(); ++i )
          {
               pkcs7OneIteration( certificateSearch, data );
               progress( i );
          }
          GetSettings()->LogStream() << "ok";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& )
     {
          if( i < GetSettings()->IterationNum() )
          {
               GetSettings()->LogStream() <<"Error: stress test fail on " <<i <<"-th iteration \n";
               GetSettings()->LogStream().flush();
          }
          throw;
     }
}

void Stress::pkcs7OneIteration( CertificateGuiSearch& _certificateSearch, const std::vector<BYTE>& _data ) const
{
     PCCERT_CONTEXT RecipientCertArray[] = { _certificateSearch.GetContext() };

     HCRYPTPROV prov = NULL; 
     if( !CryptAcquireContext( &prov, 
          NULL, 
          GetSettings()->ProvInfo().Name(),
          GetSettings()->ProvInfo().Type(),
          CRYPT_SILENT | CRYPT_VERIFYCONTEXT ) )
     {
          throw csp_exception( "CryptAcquireContext", GetLastError() );
     }

     CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm = { 0 };
     DWORD EncryptAlgSize = sizeof(EncryptAlgorithm);

     EncryptAlgorithm.pszObjId = szOID_CPCSP_ENCRYPT_ALG;  

     CRYPT_ENCRYPT_MESSAGE_PARA EncryptParams = { 0 };

     DWORD EncryptParamsSize = sizeof(EncryptParams);

     EncryptParams.cbSize =  EncryptParamsSize;
     EncryptParams.dwMsgEncodingType = MY_ENCODING_TYPE;
     EncryptParams.hCryptProv = prov;
     EncryptParams.ContentEncryptionAlgorithm = EncryptAlgorithm;

     DWORD cbEncryptedBlob = 0;

     if( !CryptEncryptMessage(
          &EncryptParams,
          1,
          RecipientCertArray,
          &_data[0],
          _data.size(),
          NULL,
          &cbEncryptedBlob))
     {
          throw csp_exception( "CryptEncryptMessage", GetLastError() );
     }
     std::vector<BYTE> encryptedBlob( cbEncryptedBlob );

     if( !CryptEncryptMessage(
          &EncryptParams,
          1,
          RecipientCertArray,
          &_data[0],
          _data.size(),
          &encryptedBlob[0],
          &cbEncryptedBlob ))
     {
          throw csp_exception( "CryptEncryptMessage", GetLastError() );
     }

     CryptReleaseContext( prov, 0 );
}

void Stress::pkcs7Sign() const
{
     GetSettings()->LogStream() << "\n\nStress::pkcs7Sign\n";
     GetSettings()->LogStream().flush();

     std::vector<BYTE> data;
     getTestPlainText( data );

     GetSettings()->LogStream() <<"Searching for certificate..\n";
     GetSettings()->LogStream().flush();

     CertificateGuiSearch certificateSearch;
     certificateSearch.FindContext();

     int i = 0;
     try
     {
          GetSettings()->LogStream() << "Stress test progress:";
          GetSettings()->LogStream().flush();
          for( i = 0; i < GetSettings()->IterationNum(); ++i )
          {
               pkcs7SignOneIteration( certificateSearch, data );
               progress( i );
          }
          GetSettings()->LogStream() << "ok";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& )
     {
          if( i < GetSettings()->IterationNum() )
          {
               GetSettings()->LogStream() <<"Error: stress test fail on " <<i <<"-th iteration \n";
               GetSettings()->LogStream().flush();
          }
          throw;
     }
}

void Stress::pkcs7SignOneIteration( CertificateGuiSearch& _certificateSearch, const std::vector<BYTE>& _data ) const
{
     //Initialize Message's and MessageSize's arrays 
     const BYTE* MessageArray[] = { &_data[0] };
     DWORD MessageSizeArray[] = { _data.size() };

     CRYPT_SIGN_MESSAGE_PARA  SigParams = { 0 };

     //Initialize the SignParams data structure
     SigParams.cbSize = sizeof(CRYPT_SIGN_MESSAGE_PARA);
     SigParams.dwMsgEncodingType = MY_ENCODING_TYPE;
     SigParams.pSigningCert = _certificateSearch.GetContext();
     SigParams.HashAlgorithm.pszObjId = szOID_CPCSP_HASH_ALG;
     SigParams.HashAlgorithm.Parameters.cbData = NULL;
     SigParams.cMsgCert = 1;
     SigParams.rgpMsgCert = &_certificateSearch.GetContext();
     SigParams.cAuthAttr = 0;
     SigParams.dwInnerContentType = 0;
     SigParams.cMsgCrl = 0;
     SigParams.cUnauthAttr = 0;
     SigParams.dwFlags = 0;
     SigParams.pvHashAuxInfo = NULL;
     SigParams.rgAuthAttr = NULL;

     DWORD cbDetachedSignatureBlob = 0;

     //Get the size of the output signature blob
     if(!CryptSignMessage(
          &SigParams,                //Signature parameters
          TRUE,                      //Detached
          1,                         //Number of messages
          MessageArray,              //Messages to be signed
          MessageSizeArray,          //Size of messages
          NULL,                      //Buffer for signature
          &cbDetachedSignatureBlob)) //Size of buffer
     {
          throw csp_exception( "CryptSignMessage", GetLastError() );
     }

     std::vector<BYTE> detachedSignature( cbDetachedSignatureBlob);

     //Sign message and get detached signature in signature blob
     if(!CryptSignMessage(
          &SigParams,               //Signature parameters
          TRUE,                     //Detached
          1,                        //Number of messages
          MessageArray,             //Messages to be signed
          MessageSizeArray,         //Size of messages
          &detachedSignature[0],  //Buffer for signature
          &cbDetachedSignatureBlob))//Size of buffer
     {
          throw csp_exception( "CryptSignMessage", GetLastError() );
     }
}

void Stress::progress( int _iteration ) const
{
     static const int PROGRESS_STEPS = 10;
     int step = GetSettings()->IterationNum() / PROGRESS_STEPS;
     if( _iteration % step == 0 )
          GetSettings()->LogStream() << ".";
}