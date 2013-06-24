/// @file
/// @brief Файл содержит определение класса, тестирующего шифрование форматированного сообщения.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef encrypt_message_h__
#define encrypt_message_h__


#include "../test-base.h"
#if defined(_WIN32)
#include "../../tools/certificate-search.h"
#endif

/// @brief Тестирует формирование и шифрование форматированного сообщения
class EncryptMessage: public TestBase
{
public:
     EncryptMessage();
     ~EncryptMessage();

     /// @brief Запуск теста.
     virtual void Run();

private:
//     void PrepareProviderContext();
/// @brief Шифрование сообщения.
     void Encrypt();
/// @brief Расшифрование сообщения.
     void Decrypt() const;

private:
//     HCRYPTPROV prov_;
     std::vector<BYTE> message_;
     std::vector<BYTE> encryptedBlob_;
#if defined(_WIN32)
     CertificateGuiSearch certificateSearch_;
#endif
};


#endif // encrypt_message_h__
