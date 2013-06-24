/// @file
/// @brief Файл содержит определения классов поиска сертификатов.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef certificate_search_h__
#define certificate_search_h__

#if defined(_WIN32)
#include <Windows.h>
#include <WinCrypt.h>
#include <Cryptuiapi.h>
#endif

class CertificateSearch
{
public:
     CertificateSearch();
     ~CertificateSearch();

     virtual void FindContext() = 0;

     void OpenStore( HCRYPTPROV _prov, LPCTSTR _storeName );
     HCERTSTORE GetStore() const;
     PCCERT_CONTEXT& GetContext();

protected:
     void SetContext( PCCERT_CONTEXT _context );

private:
     HCERTSTORE store_;
     PCCERT_CONTEXT context_;
};


class CertificateGuiSearch: public CertificateSearch
{
public:
     virtual void FindContext();
};


#endif // certificate_search_h__
