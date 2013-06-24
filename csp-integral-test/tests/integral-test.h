/// @file
/// @brief Файл содержит определение интегрального класса тестов.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef integral_test_h__
#define integral_test_h__


#include "test-base.h"


/// @brief Централизованно регистрирует тесты и запускает их.
class IntegralTest: public TestBase
{
     typedef std::list< TestBase* > TestList;

public:
     IntegralTest( const Settings& _settings );
     ~IntegralTest();

     /// @brief Запуск тестов из списка.
     virtual void Run();

     /// @brief Добавить тест в список выполнения
     /// @param _newTest Объект теста, созданный в куче. Класс сам освободит память,
     /// выделенную под _newTest, вызывающий код этого делать не должен!
     /// @throw std::invalid_argument если были переданы невалидные данные
     void AddTest( TestBase* _newTest );

private:
     const Settings& settings_;
     TestList testList_;
};


#endif // integral_test_h__
