/// \file
/// \brief ‘айл содержит определение методов класса, тестирующего работу с контейнерами на устройстве.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.



#include "stdafx.h"
#include "container.h"

void ContainerOnTheDevice::Run()
{
     GetSettings()->LogStream() << "\nContainerOnTheDevice::Run()\n" <<std::endl;

     HCRYPTPROV prov = 0;

     try
     {
          GetSettings()->LogStream() << "Acquiring provider context.." <<std::endl;

          ///ќткрытие контекста с переданным именем container и флагами flags
          if( !CryptAcquireContext( &prov, _T( "\\\\!\\" ), GetSettings()->ProvInfo().Name(), GetSettings()->ProvInfo().Type(), 0 ))
          {
               if( GetLastError() == NTE_BAD_KEYSET )
                    GetSettings()->LogStream() << "No keys found on the devise subject to possible device missing (" <<std::hex <<NTE_BAD_KEYSET << ")" <<std::endl;

               throw csp_exception( __FUNCTION__"-CryptAcquireContext", GetLastError() );
          }

          GetSettings()->LogStream() << "Getting provider's properties.." <<std::endl;
          ///ѕолучение имени контейнера
          tstring containerName;
          CryptGetProvParamToString( prov, PP_CONTAINER, containerName, 0 );
          GetSettings()->LogStream() << "Container name is " <<containerName.c_str() <<std::endl;

          ///ѕолучение уникального (полного) имени контейнера
          tstring uniqueContainerName;
          CryptGetProvParamToString( prov, PP_UNIQUE_CONTAINER, uniqueContainerName, 0 );
          GetSettings()->LogStream() << "Unique container name is " <<uniqueContainerName.c_str() <<std::endl;

          try
          {
               GetSettings()->LogStream() << "Enumerating containers.." <<std::endl;

               DWORD enumFlag = CRYPT_FIRST;
               while( true ) 
               {
                    tstring anotherContainer;
                    CryptGetProvParamToString( prov, PP_ENUMCONTAINERS, anotherContainer, enumFlag );
                    GetSettings()->LogStream() <<anotherContainer.c_str() <<std::endl;
                    enumFlag = CRYPT_NEXT;
               }
          }
          catch( csp_exception& e )
          {
               if( e.code() != ERROR_NO_MORE_ITEMS )
                    throw;
          }
          if( !CryptReleaseContext( prov, 0 )){}
     }
     catch( csp_exception& )
     {
          if( !CryptReleaseContext( prov, 0 )){}

          throw;
     }
}


void ContainerOnTheDevice::CryptGetProvParamToVector( HCRYPTPROV _prov, DWORD _paramType, std::vector<BYTE>& _param, DWORD _flags ) const throw( csp_exception )
{
     DWORD paramSize = 0;
     if( !CryptGetProvParam( _prov, _paramType, 0, &paramSize, _flags ))
          throw csp_exception( __FUNCTION__, GetLastError() );

     _param.resize( paramSize );

     if( !CryptGetProvParam( _prov, _paramType, &_param[0], &paramSize, _flags ))
          throw csp_exception( __FUNCTION__, GetLastError() );
}

void ContainerOnTheDevice::CryptGetProvParamToString( HCRYPTPROV _prov, DWORD _paramType, tstring& _param, DWORD _flags ) const throw( csp_exception )
{
     std::vector<BYTE> buf;
     CryptGetProvParamToVector( _prov, _paramType, buf, _flags );
     _param = tstring( buf.begin(), buf.end() );
}

