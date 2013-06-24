/// @file
/// @brief Файл содержит определение методов класса, тестирующего шифрование форматированного сообщения.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "encrypt-message.h"


EncryptMessage::EncryptMessage() //: prov_( 0 )
{

}

EncryptMessage::~EncryptMessage()
{
//     if( prov_ && !CryptReleaseContext( prov_, 0 ) )
//          throw csp_exception( "CryptReleaseContext", GetLastError() );
}


void EncryptMessage::Run()
{
     GetSettings()->LogStream() <<"\nEncryptMessage::Run()\n\n";
     GetSettings()->LogStream().flush();

     try
     {
          GetSettings()->LogStream() <<"Searching for certificate..\n";
          GetSettings()->LogStream().flush();

///Поиск сертификата для зашифрования сообщения
          certificateSearch_.FindContext();

          GetMessage( message_ );

//          PrepareProviderContext();
///Шифрование сообщения
          Encrypt();
///Расшифрование сообщения
          Decrypt();

          GetSettings()->LogStream() <<"Success\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() <<e.what();
     }
}


void EncryptMessage::Encrypt()
{
///Указание сертификата для шифрования
     PCCERT_CONTEXT RecipientCertArray[] = { certificateSearch_.GetContext() };

///Открытие контекста криптопровайдера prov в памяти для зашифрования
     HCRYPTPROV prov = NULL; 
     if( !CryptAcquireContext( &prov, 
          NULL, 
          GetSettings()->ProvInfo().Name(),
          GetSettings()->ProvInfo().Type(),
          CRYPT_SILENT | CRYPT_VERIFYCONTEXT ) )
     {
          throw csp_exception( "CryptAcquireContext", GetLastError() );
     }

///Заполнение структуры CRYPT_ENCRYPT_MESSAGE_PARA
     CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm = { 0 };
     DWORD EncryptAlgSize = sizeof(EncryptAlgorithm);
///Алгоритм szOID_CPCSP_ENCRYPT_ALG
     EncryptAlgorithm.pszObjId = szOID_CPCSP_ENCRYPT_ALG;  

     CRYPT_ENCRYPT_MESSAGE_PARA EncryptParams = { 0 };

     DWORD EncryptParamsSize = sizeof(EncryptParams);

     EncryptParams.cbSize =  EncryptParamsSize;
///Тип кодировки (DER)
     EncryptParams.dwMsgEncodingType = MY_ENCODING_TYPE;

///Дескриптор криптопровайдера prov
     EncryptParams.hCryptProv = prov;
     EncryptParams.ContentEncryptionAlgorithm = EncryptAlgorithm;


     GetSettings()->LogStream() <<"Getting size of encrypted message..\n";
     GetSettings()->LogStream().flush();

     DWORD cbEncryptedBlob = 0;

///Вызов функции CryptEncryptMessage
     if( !CryptEncryptMessage(
          &EncryptParams,
          1,
          RecipientCertArray,
          &message_[0],
          message_.size(),
          NULL,
          &cbEncryptedBlob))
     {
          throw csp_exception( "CryptEncryptMessage", GetLastError() );
     }

     encryptedBlob_.assign( cbEncryptedBlob, 0 );

     GetSettings()->LogStream() <<"Encrypting message..\n";
     GetSettings()->LogStream().flush();

     if( !CryptEncryptMessage(
          &EncryptParams,
          1,
          RecipientCertArray,
          &message_[0],
          message_.size(),
          &encryptedBlob_[0],
          &cbEncryptedBlob ))
     {
          throw csp_exception( "CryptEncryptMessage", GetLastError() );
     }

     CryptReleaseContext( prov, 0 );
}

void EncryptMessage::Decrypt() const
{
///Определение хранилища личных сертификатов для поиска ключа
     HCERTSTORE CertStoreArray[] = { certificateSearch_.GetStore() };

///Заполнение структуры CRYPT_DECRYPT_MESSAGE_PARA
     CRYPT_DECRYPT_MESSAGE_PARA  DecryptParams = { 0 };
     DWORD  DecryptParamsSize = sizeof(DecryptParams);
     DecryptParams.cbSize = DecryptParamsSize;
     DecryptParams.dwMsgAndCertEncodingType = MY_ENCODING_TYPE;
     DecryptParams.cCertStore = 1;
     DecryptParams.rghCertStore = CertStoreArray;

     GetSettings()->LogStream() <<"Getting size of decrypted message..\n";
     GetSettings()->LogStream().flush();

///Вызов функции CryptDecryptMessage
     DWORD cbDecryptedMessage = 0;
     if( !CryptDecryptMessage(
          &DecryptParams,
          &encryptedBlob_[0],
          encryptedBlob_.size(),
          NULL,
          &cbDecryptedMessage,
          NULL))
     {
          throw csp_exception( "CryptDecryptMessage", GetLastError() );
     }

     std::vector<BYTE> decryptedMessage( cbDecryptedMessage );

     GetSettings()->LogStream() <<"Decrypting message..\n";
     GetSettings()->LogStream().flush();

     if( !CryptDecryptMessage(
          &DecryptParams,
          &encryptedBlob_[0],
          encryptedBlob_.size(),
          &decryptedMessage[0],
          &cbDecryptedMessage,
          NULL))
     {
          throw csp_exception( "CryptDecryptMessage", GetLastError() );
     }
}

/*
void EncryptMessage::PrepareProviderContext()
{
     CreateContainerIfNotExists();

     GetSettings()->LogStream() << "Acquiring provider context..\n";
     GetSettings()->LogStream().flush();

     if( !CryptAcquireContext( 
          &prov_, 
          GetSettings()->Container(), 
          GetSettings()->ProvInfo().Name(),
          GetSettings()->ProvInfo().Type(),
          0 ))
     {
          throw csp_exception( "CryptAcquireContext", GetLastError() );
     }
}
*/
