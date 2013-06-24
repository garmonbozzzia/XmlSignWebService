/// @file
/// @brief Файл содержит определение методов, тестирующего экспорт ключей.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef exportation_h__
#define exportation_h__


#include "../test-base.h"


/// @brief Тестирует работу экспорта ключей
class Exportation: public TestBase
{
public:
     Exportation(){}
     ~Exportation(){}

     /// @brief Запуск теста.
     virtual void Run();
};


#endif // exportation_h__
