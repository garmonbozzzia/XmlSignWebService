/// @file
/// @brief Файл содержит определение класса, тестирующего генерацию ключей.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef key_generation_h__
#define key_generation_h__


#include "../test-base.h"


/// @brief Тестирует работу генерации ключей
class KeyGeneration: public TestBase
{
public:
     KeyGeneration(){}
     ~KeyGeneration(){}

     /// @brief Запуск теста.
     virtual void Run();
};


#endif // key_generation_h__
