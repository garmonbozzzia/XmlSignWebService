/// @file
/// @brief Файл содержит точку входа в интегральный тест.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.

#include "stdafx.h"

#include "tests/capi-1/key-generation.h"
#include "tests/capi-1/encryption.h"
#include "tests/capi-1/exportation.h"
#include "tests/capi-1/signing.h"
#include "tests/capi-1/diffie-hellman.h"
#include "tests/capi-2/sign-message.h"
#include "tests/capi-2/encrypt-message.h"
#include "tests/multithread/multithread.h"
#include "tests/stress/stress.h"
#include "tests/container/container.h"
#include "tests/integral-test.h"

int _tmain(int argc, _TCHAR* argv[])
{
     try
     {
          ProviderInfo provInfo;
          provInfo.Name( VPN_DEF_PROV );
          provInfo.Type( VPN_PROV_TYPE );
          provInfo.SessionKeyAlgId( CPCSP_ENCRYPT_ID );

          CmdLineInput cmd( argc, argv );

          Settings settings( cmd, provInfo );
          
          IntegralTest integral( settings );
          //integral.AddTest( new KeyGeneration );
          //integral.AddTest( new Encryption );
          //integral.AddTest( new Exportation );
          integral.AddTest( new Hash );
          integral.AddTest( new Signing );
          //integral.AddTest( new DiffieHellman );
          //integral.AddTest( new EncryptMessage );
          //integral.AddTest( new SignMessage );
          //integral.AddTest( new Multithread );
          //integral.AddTest( new Stress );
          //integral.AddTest( new ContainerOnTheDevice );
          integral.Run();
     }
     catch( std::exception& e )
     {
          std::cerr <<"\n" <<e.what() <<"\n";          
     }
     return 0; 
}


