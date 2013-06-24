/// @file
/// @brief Файл содержит определение класса, тестирующего работу алгоритма Диффи-Хеллмана.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef diffie_hellman_h__
#define diffie_hellman_h__


#include "../test-base.h"


/// @brief Тестирует работу алгоритма Диффи-Хеллмана
class DiffieHellman: public TestBase
{
public:
     DiffieHellman();
     ~DiffieHellman();

     /// @brief Запуск теста.
     virtual void Run(); 

private:
     /// @brief Сормировать ключи обмена.
     void MakeDhKeys();
     /// @brief Проверить идентичность сформированных ключей обмена.
     void CheckDhKeys();

     void SetNullInitVector( HCRYPTKEY _key );

private:
          HCRYPTPROV prov1;
          HCRYPTPROV prov2;
          HCRYPTKEY exchangeKey1;
          HCRYPTKEY exchangeKey2; 
          HCRYPTKEY sessionKey; 
          HCRYPTKEY importedSessionKey;
};


#endif // diffie_hellman_h__
