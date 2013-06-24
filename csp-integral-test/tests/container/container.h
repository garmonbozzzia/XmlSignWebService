/// @file
/// @brief ‘айл содержит определение класса, тестирующего работу с контейнерами на устройстве.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef CONTAINER_H__
#define container_h__


#include "../test-base.h"


/// @brief “естирует работу с контейнерами на устройстве
class ContainerOnTheDevice: public TestBase
{
public:
     /// @brief «апуск теста.
     virtual void Run();
private:
     ///@brief ѕолучение параметров контейнера
     void CryptGetProvParamToVector( HCRYPTPROV _prov, DWORD _paramType, std::vector<BYTE>& _param, DWORD _flags ) const throw( csp_exception );
     void CryptGetProvParamToString( HCRYPTPROV _prov, DWORD _paramType, tstring& _param, DWORD _flags ) const throw( csp_exception );
};


#endif // container_h__