/// @file
/// @brief Файл содержит определение класса, тестирующего шифрование.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef encryption_h__
#define encryption_h__


#include "../test-base.h"


/// @brief Тестирует работу алгоритма шифрования
class Encryption: public TestBase
{
public:
     Encryption(){}
     ~Encryption(){}

     /// @brief Запуск теста.
     virtual void Run();
};


#endif // encryption_h__
