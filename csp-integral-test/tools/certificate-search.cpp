/// @file
/// @brief Файл содержит определение методов классов поиска сертификатов.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.

#include "stdafx.h"
#include "certificate-search.h"


CertificateSearch::CertificateSearch()
: store_( 0 )
, context_( 0 )
{
     OpenStore( 0, _T( "MY" ) );
}

CertificateSearch::~CertificateSearch()
{
     CertCloseStore( store_, 0 );
     CertFreeCertificateContext( context_ );
}

void CertificateSearch::OpenStore( HCRYPTPROV _prov, LPCTSTR _storeName )
{
     CertCloseStore( store_, 0 );

     store_ = CertOpenSystemStore( _prov, _storeName );
     if( !store_ )
          throw csp_exception( "CertOpenSystemStore", GetLastError() );
}

PCCERT_CONTEXT& CertificateSearch::GetContext()
{
     return context_;
}

HCERTSTORE CertificateSearch::GetStore() const
{
     return store_;
}

void CertificateSearch::SetContext( PCCERT_CONTEXT _context )
{
     context_ = _context;
}

void CertificateGuiSearch::FindContext()
{
     PCCERT_CONTEXT context = CryptUIDlgSelectCertificateFromStore(
          GetStore(),
          NULL,
          NULL,
          NULL,
          CRYPTUI_SELECT_LOCATION_COLUMN,
          0,
          NULL );

     if( !context )
          throw csp_exception( "CryptUIDlgSelectCertificateFromStore", GetLastError() );

     SetContext( context );
}


