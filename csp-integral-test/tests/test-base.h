/// @file
/// @brief Файл содержит определение базового тестового класса.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef test_base_h__
#define test_base_h__


#include "../defines.h"
#include "../tools/settings.h"


/// @brief Базовый класс для тестов.
class TestBase
{
public:
     /// @brief Запуск теста.
     virtual void Run() = 0;
     virtual ~TestBase(){}

     TestBase();
     
     /// @brief Запуск теста с перехватом исключения и выводом сообщения об ошибке.
     void SafeRun();

     /// @brief Задать настройки для теста.
     /// @param _settings Настройки для теста.
     void SetSettings( const Settings* _settings );

     /// @brief Получить настройки для теста.
     /// @return Настройки для теста.
     const Settings* GetSettings() const;

protected:
     /// @brief Отркрыть контекст криптопровайдера. 
     /// Если ключевой контейнер, на который ссылается контекст, не существует, то он будет создан.
     /// @param[out] _prov Хендл контекста.
     /// @param _withGui Интерактивный режим работы с контекстом криптопровайдера.
     void CreateContainerIfNotExists( HCRYPTPROV& _prov, bool _withGui = false  ) const;

     /// @brief Получить ключ из контейнера, если ключ не существует - создать.
     /// @param _prov Хендл контекста, связанного с ключевым контейнером.
     /// @param _alg Идентификатор алгоритма ключа.
     /// @param[out] _key Хендл ключа
     void CreateKeyIfNotExists( HCRYPTKEY _prov, ALG_ID _alg, HCRYPTKEY& _key ) const;

     void GetMessage( std::vector<BYTE>& _buffer ) const;
     
private:
     const Settings* settings_;
};


#endif // test_base_h__