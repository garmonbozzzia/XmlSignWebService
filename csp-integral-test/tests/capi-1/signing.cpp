/// @file
/// @brief Файл содержит определение методов класса, тестирующего ЭЦП.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "signing.h"

void Hash::GetMyMessage( std::vector<BYTE>& _buffer ) const
{
  std::string message("This is message, length=32 bytes");
  _buffer.resize(32);
  std::memcpy(&_buffer[0], message.c_str(), 32);
  return;
}


void Hash::Run()
{
  HCRYPTPROV prov = 0;
  HCRYPTKEY keyPair = 0, publicKey = 0;
  HCRYPTHASH hash = 0, doubleHash = 0;

  try
  {
    CreateContainerIfNotExists( prov );
    CreateContainerIfNotExists( prov );
    GetSettings()->csp()->SetProvParam( prov, PP_SIGNATURE_PIN, (LPBYTE)"Asdf1234--", 0);
    CreateKeyIfNotExists( prov, AT_SIGNATURE, keyPair );
    if(!GetSettings()->csp()->CreateHash( prov, CPCSP_HASH_ID, 0, 0, &hash ) )
	    throw csp_exception( "CryptCreateHash", GetLastError() );

    std::vector<BYTE> message;
    GetMyMessage( message );
    
    if( !GetSettings()->csp()->HashData( hash, &message[0], message.size(), 0 ) )
      throw csp_exception( "GetSettings()->csp()->HashData", GetLastError() );

    std::vector<BYTE> hashValue;
    DWORD size = 32;
    hashValue.resize(size);
    
    if( !GetSettings()->csp()->GetHashParam( hash, HP_HASHVAL, &hashValue[0], &size, 0))
      throw csp_exception( "GetSettings()->csp()->GetHashParam", GetLastError() );      
  }
  catch( csp_exception& e )
  {
      GetSettings()->LogStream() << e.what() <<"\n";
      GetSettings()->LogStream().flush();
  }
  if( hash && !GetSettings()->csp()->DestroyHash( hash ) )
      throw csp_exception( "GetSettings()->csp()->DestroyHash", GetLastError() );
  if( doubleHash && !GetSettings()->csp()->DestroyHash( doubleHash ) )
      throw csp_exception( "GetSettings()->csp()->DestroyHash", GetLastError() );
  if( keyPair && !GetSettings()->csp()->DestroyKey( keyPair ) )
      throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );
  if( prov && !GetSettings()->csp()->ReleaseContext( prov, 0 ) )
      throw csp_exception( "GetSettings()->csp()->ReleaseContext", GetLastError() );
}

void Signing::Run()
{
     GetSettings()->LogStream() <<"\nSigning::Run()\n\n";
     GetSettings()->LogStream().flush();

     HCRYPTPROV prov = 0;
     HCRYPTKEY keyPair = 0, publicKey = 0;
     HCRYPTHASH hash = 0, doubleHash = 0;

     try
     {
          CreateContainerIfNotExists( prov );

          GetSettings()->LogStream() << "Acquiring provider context..\n";
          GetSettings()->LogStream().flush();

///Создание или открытие существующего контейнера
          CreateContainerIfNotExists( prov );

///Выставить пароль доступа к ключам контейнера PP_SIGNATURE_PIN 
          GetSettings()->csp()->SetProvParam( prov, PP_SIGNATURE_PIN, (LPBYTE)"Asdf1234", 0);

///Создание или получение дескриптора существующего ключа
          CreateKeyIfNotExists( prov, AT_SIGNATURE, keyPair );

///Открытие контекста хеширования
          if(!GetSettings()->csp()->CreateHash( prov, CPCSP_HASH_ID, 0, 0, &hash ) )
	      throw csp_exception( "CryptCreateHash", GetLastError() );

          std::vector<BYTE> message;
          GetMessage( message );

///Хеширование данных
          GetSettings()->LogStream() << "Hashing..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->HashData( hash, &message[0], message.size(), 0 ) )
               throw csp_exception( "GetSettings()->csp()->HashData", GetLastError() );

          GetSettings()->LogStream() << "Duplicating hash object..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->DuplicateHash( hash, 0, 0, &doubleHash ) )
               throw csp_exception( "GetSettings()->csp()->DuplicateHash", GetLastError() );
          if(ERROR_MORE_DATA == HP_HASHVAL){}
///Подпись данных
          GetSettings()->LogStream() << "Getting singnature size..\n";
          GetSettings()->LogStream().flush();
          DWORD sigLen = 0;
          if( !GetSettings()->csp()->SignHash( hash, AT_SIGNATURE, 0, 0, 0, &sigLen ) )
               throw csp_exception( "GetSettings()->csp()->SignHash", GetLastError() );
          std::vector<BYTE> signature( sigLen );

          GetSettings()->LogStream() << "Signing..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->SignHash( hash, AT_SIGNATURE, 0, 0, &signature[0], &sigLen ) )
               throw csp_exception( "GetSettings()->csp()->SignHash", GetLastError() );

///Экспорт открытого ключа для проверки подписи
          GetSettings()->LogStream() << "Getting size of PUBLICKEYBLOB..\n";
          GetSettings()->LogStream().flush();
          DWORD blobSize = 0;
          if( !GetSettings()->csp()->ExportKey( keyPair, 0, PUBLICKEYBLOB, 0, 0, &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          GetSettings()->LogStream() << "Exporting public key..\n";
          GetSettings()->LogStream().flush();
          std::vector<BYTE> publicBlob( blobSize );
          if( !GetSettings()->csp()->ExportKey( keyPair, 0, PUBLICKEYBLOB, 0, &publicBlob[0], &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

///Импорт открытого ключа для проверки подписи publicKey
          GetSettings()->LogStream() << "Importing public key to the same provider context..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->ImportKey( prov, &publicBlob[0], publicBlob.size(), 0, 0, &publicKey ) )
               throw csp_exception( "GetSettings()->csp()->ImportKey", GetLastError() );

///Проверка подписи с использованием ключа publicKey
          GetSettings()->LogStream() << "Verifying signature..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->VerifySignature( doubleHash, &signature[0], signature.size(), publicKey, 0, 0 ) )
               throw csp_exception( "GetSettings()->csp()->VerifySignature", GetLastError() );

          GetSettings()->LogStream() << "Success\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() << e.what() <<"\n";
          GetSettings()->LogStream().flush();
     }
     if( hash && !GetSettings()->csp()->DestroyHash( hash ) )
          throw csp_exception( "GetSettings()->csp()->DestroyHash", GetLastError() );
     if( doubleHash && !GetSettings()->csp()->DestroyHash( doubleHash ) )
          throw csp_exception( "GetSettings()->csp()->DestroyHash", GetLastError() );
     if( keyPair && !GetSettings()->csp()->DestroyKey( keyPair ) )
          throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );
     if( prov && !GetSettings()->csp()->ReleaseContext( prov, 0 ) )
          throw csp_exception( "GetSettings()->csp()->ReleaseContext", GetLastError() );
}
