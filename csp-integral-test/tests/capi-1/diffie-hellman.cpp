/// @file
/// @brief Файл содержит определение методов класса, тестирующего работу алгоритма Диффи-Хеллмана.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.


#include "stdafx.h"
#include "diffie-hellman.h"


DiffieHellman::DiffieHellman() 
: prov1( 0 )
, prov2( 0 )
, exchangeKey1( 0 )
, exchangeKey2( 0 )
, sessionKey( 0 ) 
, importedSessionKey( 0 )
{

}


DiffieHellman::~DiffieHellman()
{
     if( exchangeKey1 )
          GetSettings()->csp()->DestroyKey( exchangeKey1 );
     if( exchangeKey2 )
          GetSettings()->csp()->DestroyKey( exchangeKey2 );
     if( sessionKey )
          GetSettings()->csp()->DestroyKey( sessionKey );
     if( importedSessionKey )
          GetSettings()->csp()->DestroyKey( importedSessionKey );
     if( prov1 )
          GetSettings()->csp()->ReleaseContext( prov1, 0 );
     if( prov2 )
          GetSettings()->csp()->ReleaseContext( prov2, 0 );
}


void DiffieHellman::Run()
{
     GetSettings()->LogStream() <<"\nDiffieHellman::Run()\n\n";
     GetSettings()->LogStream().flush();

     try
     {
          /// Формируем ключи обмена.
          MakeDhKeys();
          /// Проверяем их идентичность.
          CheckDhKeys();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() << e.what() <<"\n";
          GetSettings()->LogStream().flush();
     }
}


void DiffieHellman::MakeDhKeys()
{
     HCRYPTKEY keypair1 = 0, keypair2 = 0;

     try
     {
          GetSettings()->LogStream() << "Acquiring virtual provider context 1..\n";
          GetSettings()->LogStream().flush();
///Открытие контекста prov1 в памяти
          if( !GetSettings()->csp()->AcquireContext( &prov1, 
               0, 
               GetSettings()->ProvInfo().Name(),
               GetSettings()->ProvInfo().Type(),
               CRYPT_VERIFYCONTEXT ) )
          {
               throw csp_exception( "GetSettings()->csp()->AcquireContext", GetLastError() );
          }

          GetSettings()->LogStream() <<"Creating key pair 1..\n";
          GetSettings()->LogStream().flush();
///Формирование ключевой пары keypair1 для DH
          if( !GetSettings()->csp()->GenKey( prov1, AT_KEYEXCHANGE, 0, &keypair1 ) )
               throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );

          GetSettings()->LogStream() << "Acquiring virtual provider context 2..\n";
          GetSettings()->LogStream().flush();
///Открытие контекста prov2 в памяти
          if( !GetSettings()->csp()->AcquireContext( &prov2, 
               0, 
               GetSettings()->ProvInfo().Name(),
               GetSettings()->ProvInfo().Type(),
               CRYPT_VERIFYCONTEXT ) )
          {
               throw csp_exception( "GetSettings()->csp()->AcquireContext", GetLastError() );
          }

          GetSettings()->LogStream() <<"Creating key pair 2..\n";
          GetSettings()->LogStream().flush();
///Формирование ключевой пары keypair2 для DH
          if( !GetSettings()->csp()->GenKey( prov2, AT_KEYEXCHANGE, 0, &keypair2 ) )
               throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );

          GetSettings()->LogStream() << "Getting size of PUBLICKEYBLOB..\n";
          GetSettings()->LogStream().flush();
          DWORD blobSize = 0;
///Экспорт открытого ключа из keypair1
          if( !GetSettings()->csp()->ExportKey( keypair1, 0, PUBLICKEYBLOB, 0, 0, &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          GetSettings()->LogStream() << "Exporting public key 1 from provider context 1..\n";
          GetSettings()->LogStream().flush();
          std::vector<BYTE> publicBlob1( blobSize );
          if( !GetSettings()->csp()->ExportKey( keypair1, 0, PUBLICKEYBLOB, 0, &publicBlob1[0], &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          GetSettings()->LogStream() << "Exporting public key 2 from provider context 2..\n";
          GetSettings()->LogStream().flush();
          std::vector<BYTE> publicBlob2( blobSize );
///Экспорт открытого ключа из keypair2
          if( !GetSettings()->csp()->ExportKey( keypair2, 0, PUBLICKEYBLOB, 0, &publicBlob2[0], &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          GetSettings()->LogStream() << "Making exchange key 1..\n";
          GetSettings()->LogStream().flush();
///Импорт открытого ключа из keypair2 в prov1, выработка общего ключа DH exchangeKey1
          if( !GetSettings()->csp()->ImportKey( prov1, &publicBlob2[0], publicBlob2.size(), keypair1, 0, &exchangeKey1 ) )
               throw csp_exception( "GetSettings()->csp()->ImportKey", GetLastError() );

          GetSettings()->LogStream() << "Making exchange key 2..\n";
          GetSettings()->LogStream().flush();
///Импорт открытого ключа из keypair1 в prov2, выработка общего ключа DH exchangeKey2
          if( !GetSettings()->csp()->ImportKey( prov2, &publicBlob1[0], publicBlob1.size(), keypair2, 0, &exchangeKey2 ) )
               throw csp_exception( "GetSettings()->csp()->ImportKey", GetLastError() );

          /// Генерируем сессионный ключ в контексте prov1.
          GetSettings()->LogStream() << "Generating session key.." << std::endl;
          if( !GetSettings()->csp()->GenKey( prov1, GetSettings()->ProvInfo().SessionKeyAlgId(), CRYPT_EXPORTABLE, &sessionKey ))
               throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );

          SetNullInitVector( sessionKey );

          /// Экспортируем сессионный ключ из контекста prov1.
          GetSettings()->LogStream() << "Exporting session key from provider context 1..\n";
          GetSettings()->LogStream().flush();
          DWORD simpleBlobSize = 0;
          if( !GetSettings()->csp()->ExportKey( sessionKey, exchangeKey1, SIMPLEBLOB, 0, 0, &simpleBlobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey - getting size", GetLastError() );

          std::vector<BYTE> simpleBlob( simpleBlobSize );

          if( !GetSettings()->csp()->ExportKey( sessionKey, exchangeKey1, SIMPLEBLOB, 0, &simpleBlob[0], &simpleBlobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          /// Импортируем сессионный ключ в контекст prov2.
          GetSettings()->LogStream() << "Importing session key to provider context 2..\n";
          GetSettings()->LogStream().flush();

          if( !GetSettings()->csp()->ImportKey( prov2, &simpleBlob[0], simpleBlob.size(), exchangeKey2, 0, &importedSessionKey ) )
               throw csp_exception( "GetSettings()->csp()->ImportKey", GetLastError() );

          SetNullInitVector( importedSessionKey );
     }
     catch ( csp_exception& )
     {
          if( keypair1 )
               GetSettings()->csp()->DestroyKey( keypair1 );
          if( keypair2 )
               GetSettings()->csp()->DestroyKey( keypair2 );
          throw;
     }
     if( keypair1 && !GetSettings()->csp()->DestroyKey( keypair1 ) )
          throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );
     if( keypair2 && !GetSettings()->csp()->DestroyKey( keypair2 ) )
          throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );
}


void DiffieHellman::CheckDhKeys()
{
     GetSettings()->LogStream() <<"Checking DH key exchange:" <<std::endl;

     std::vector<BYTE> plain;
     GetMessage( plain );

     /// Зашифровываем тестовый текст на сессионном ключе в контексте prov1.
     GetSettings()->LogStream() <<"Encrypting message with session key in provider context 1.." <<std::endl;

     DWORD outputSize = plain.size();
     if( !GetSettings()->csp()->Encrypt( sessionKey, 0, true, 0, 0, &outputSize, plain.size() ))
          throw csp_exception( "GetSettings()->csp()->Encrypt - getting size", GetLastError() );

     std::vector<BYTE> encrypted( outputSize );
     std::copy( plain.begin(), plain.end(), encrypted.begin() );

     if( !GetSettings()->csp()->Encrypt( sessionKey, 0, true, 0, &encrypted[0], &outputSize, encrypted.size() ))
          throw csp_exception( "GetSettings()->csp()->Encrypt", GetLastError() );

     /// Расшифровываем полученный шифртекст на импортированном ключе в контексте prov2.
     GetSettings()->LogStream() <<"Decrypting with imported session key in provider context 2.." <<std::endl;

     DWORD decryptedSize = encrypted.size();
     std::vector<BYTE> decrypted( encrypted.begin(), encrypted.end() );

     if( !GetSettings()->csp()->Decrypt( importedSessionKey, 0, true, 0, &decrypted[0], &decryptedSize ) )
          throw csp_exception( "GetSettings()->csp()->Decrypt", GetLastError() );

     decrypted.resize( decryptedSize );
     if( decrypted != plain )
          GetSettings()->LogStream() <<"Error: decrypted is not match to plain" <<std::endl;
     else
          GetSettings()->LogStream() <<"Success" <<std::endl;
}

void DiffieHellman::SetNullInitVector( HCRYPTKEY _key )
{
     DWORD ivSize = 0;
     if( !GetSettings()->csp()->GetKeyParam( _key, KP_IV, 0, &ivSize, 0 ))
          throw csp_exception( "GetSettings()->csp()->GetKeyParam", GetLastError() );

     std::vector<BYTE> param( ivSize, 0 );

     if( !GetSettings()->csp()->SetKeyParam( _key, KP_IV, &param[0], 0 ) )
          throw csp_exception( "GetSettings()->csp()->SetKeyParam", GetLastError() );
}