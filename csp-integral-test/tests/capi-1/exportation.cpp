/// @file
/// @brief Файл содержит определение методов класса, тестирующего экспорт ключей.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "exportation.h"



void Exportation::Run()
{
     GetSettings()->LogStream() <<"\nExportation::Run()\n\n";
     GetSettings()->LogStream().flush();

     HCRYPTPROV prov1 = 0, prov2 = 0;
     HCRYPTKEY key1 = 0, key2 = 0;
     try
     {
          GetSettings()->LogStream() << "Acquiring provider context 1..\n";
          GetSettings()->LogStream().flush();

///Создание контейнера или открытие существующего, созданного ранее
          CreateContainerIfNotExists( prov1 );

///Выставляем пароль доступа к ключам в контейнере (PP_SIGNATURE_PIN)
          GetSettings()->csp()->SetProvParam( prov1, PP_SIGNATURE_PIN, (LPBYTE)"111111", 0);

///Формирование или получение дескриптора ключевой пары AT_SIGNATURE
          CreateKeyIfNotExists( prov1, AT_SIGNATURE, key1 );

          GetSettings()->LogStream() << "Getting size of PUBLICKEYBLOB..\n";
          GetSettings()->LogStream().flush();
          DWORD blobSize = 0;

///Экспорт открытого ключа ключевой пары
          if( !GetSettings()->csp()->ExportKey( key1, 0, PUBLICKEYBLOB, 0, 0, &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          GetSettings()->LogStream() << "Exporting public key..\n";
          GetSettings()->LogStream().flush();
          std::vector<BYTE> publicBlob( blobSize );
          if( !GetSettings()->csp()->ExportKey( key1, 0, PUBLICKEYBLOB, 0, &publicBlob[0], &blobSize ) )
               throw csp_exception( "GetSettings()->csp()->ExportKey", GetLastError() );

          
///Открытие контейнера в памяти prov2
          GetSettings()->LogStream() << "Acquiring virtual provider context 2..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->AcquireContext( &prov2, 
               0, 
               GetSettings()->ProvInfo().Name(),
               GetSettings()->ProvInfo().Type(),
               CRYPT_VERIFYCONTEXT ) )
          {
               throw csp_exception( "GetSettings()->csp()->AcquireContext", GetLastError() );
          }

///Импорт открытого ключа в prov2 для проверки ЭЦП
          GetSettings()->LogStream() << "Importing public key from provider context 1 to context 2..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->ImportKey( prov2, &publicBlob[0], publicBlob.size(), 0, 0, &key2 ) )
               throw csp_exception( "GetSettings()->csp()->ImportKey", GetLastError() );

          GetSettings()->LogStream() <<"Success\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() << e.what() <<"\n";
          GetSettings()->LogStream().flush();
     }
     if( key1 && !GetSettings()->csp()->DestroyKey( key1 ) )
          throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );
     if( key2 && !GetSettings()->csp()->DestroyKey( key2 ) )
          throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );
     if( prov1 && !GetSettings()->csp()->ReleaseContext( prov1, 0 ) )
          throw csp_exception( "GetSettings()->csp()->ReleaseContext", GetLastError() );
     if( prov2 && !GetSettings()->csp()->ReleaseContext( prov2, 0 ) )
          throw csp_exception( "GetSettings()->csp()->ReleaseContext", GetLastError() );
}