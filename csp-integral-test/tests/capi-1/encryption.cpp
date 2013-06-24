/// @file
/// @brief Файл содержит определение методов класса, тестирующего шифрование.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "encryption.h"


void Encryption::Run()
{
     GetSettings()->LogStream() << "\nEncryption::Run()\n\n";
     GetSettings()->LogStream().flush();

     HCRYPTKEY prov = 0;
     HCRYPTKEY key = 0;

     try
     {
		 GetSettings()->LogStream() << "Acquiring provider context..\n";
		 GetSettings()->LogStream().flush();

///Создание контейнера или открытие существующего, созданного ранее
          CreateContainerIfNotExists( prov );
///Выставляем пароль доступа к ключам в контейнере (PP_SIGNATURE_PIN)
          GetSettings()->csp()->SetProvParam( prov, PP_SIGNATURE_PIN, (LPBYTE)"111111", 0);

          GetSettings()->LogStream() << "Generating session key..\n";
          GetSettings()->LogStream().flush();

///Формирование сессионного ключа шифрования key
          if( !GetSettings()->csp()->GenKey( prov, GetSettings()->ProvInfo().SessionKeyAlgId(), 0, &key ) )
               throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );

          std::vector<BYTE> encrypted;
///Считать сообщение из файла
          GetMessage( encrypted );

          GetSettings()->LogStream() <<"Encrypting..\n";
          GetSettings()->LogStream().flush();
          DWORD outputSize = encrypted.size();

///Зашифровать сообщение на ключе key
          if( !GetSettings()->csp()->Encrypt( key, 0, true, 0, &encrypted[0], &outputSize, encrypted.size() ))
               throw csp_exception( "GetSettings()->csp()->Encrypt", GetLastError() );

          GetSettings()->LogStream() <<"Decrypting..\n";
          GetSettings()->LogStream().flush();

///Расшифровать сообщение на ключе key
          if( !GetSettings()->csp()->Decrypt( key, 0, true, 0, &encrypted[0], &outputSize ) )
               throw csp_exception( "GetSettings()->csp()->Decrypt", GetLastError() );

          GetSettings()->LogStream() <<"Success\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() << e.what() <<"\n";
          GetSettings()->LogStream().flush();
     }
     if( key && !GetSettings()->csp()->DestroyKey( key ) )
          throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );

     if( prov && !GetSettings()->csp()->ReleaseContext( prov, 0 ) )
          throw csp_exception( "GetSettings()->csp()->ReleaseContext", GetLastError() );
}