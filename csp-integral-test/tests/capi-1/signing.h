/// @file
/// @brief Файл содержит определение класса, тестирующего ЭЦП.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef signing_h__
#define signing_h__


#include "../test-base.h"


/// @brief Тестирует работу алгоритма подписи
class Hash: public TestBase
{
public:
     Hash(){}
     ~Hash(){}

     void GetMyMessage( std::vector<BYTE>& _buffer ) const;

     /// @brief Запуск теста.
     virtual void Run();
};

/// @brief Тестирует работу алгоритма подписи
class Signing: public TestBase
{
public:
     Signing(){}
     ~Signing(){}

     /// @brief Запуск теста.
     virtual void Run();
};


#endif // signing_h__
