/// @file
/// @brief Файл содержит определение методов класса, тестирующего генерацию ключей.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "key-generation.h"




void KeyGeneration::Run()
{
     GetSettings()->LogStream() << "\nKeyGeneration::Run()\n\n";
     GetSettings()->LogStream().flush();

     HCRYPTKEY prov = 0;

     try
     {
///Окрытие контейнера в памяти prov
          GetSettings()->LogStream() << "Acquiring virtual provider context..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->AcquireContext( &prov, 
               0, 
               GetSettings()->ProvInfo().Name(),
               GetSettings()->ProvInfo().Type(),
               CRYPT_VERIFYCONTEXT ) )
          {
               throw csp_exception( "GetSettings()->csp()->AcquireContext", GetLastError() );
          }

///Формирование симметричного ключа
          GetSettings()->LogStream() << "Generating simmetric key..\n";
          GetSettings()->LogStream().flush();
          HCRYPTKEY simmetricKey = 0;
          if( !GetSettings()->csp()->GenKey( prov, GetSettings()->ProvInfo().SessionKeyAlgId(), 0, &simmetricKey ) )
               throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );

          GetSettings()->LogStream() << "Destroying simmetric key..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->DestroyKey( simmetricKey ) )
               throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );

///Формирование ключевой пары AT_SIGNATURE
          GetSettings()->LogStream() << "Generating asimmetric key pair..\n";
          GetSettings()->LogStream().flush();
          HCRYPTKEY asimmetricKeyPair = 0;
          if( !GetSettings()->csp()->GenKey( prov, AT_SIGNATURE, 0, &simmetricKey ) )
               throw csp_exception( "GetSettings()->csp()->GenKey", GetLastError() );

          GetSettings()->LogStream() << "Destroying asimmetric key pair..\n";
          GetSettings()->LogStream().flush();
          if( !GetSettings()->csp()->DestroyKey( simmetricKey ) )
               throw csp_exception( "GetSettings()->csp()->DestroyKey", GetLastError() );

          GetSettings()->LogStream() <<"Success\n";
          GetSettings()->LogStream().flush();
     }
     catch( csp_exception& e )
     {
          GetSettings()->LogStream() << e.what() <<"\n";
          GetSettings()->LogStream().flush();
     }
     if( prov && !GetSettings()->csp()->ReleaseContext( prov, 0 ) )
          throw csp_exception( "GetSettings()->csp()->ReleaseContext", GetLastError() );
}


