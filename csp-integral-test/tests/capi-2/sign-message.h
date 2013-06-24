/// @file
/// @brief Файл содержит определение класса, тестирующего подпись форматированного сообщения.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef sign_message_h__
#define sign_message_h__

#include "../test-base.h"
#if defined(_WIN32)
#include "../../tools/certificate-search.h"
#endif

/// @brief Тестирует подпись форматированного сообщения
class SignMessage: public TestBase
{
public:
     SignMessage();
     ~SignMessage(){}

     /// @brief Запуск теста.
     virtual void Run(); 

private:
     void MakeSignature();
     void VerifySignature() const;

     void WriteSignatureToFile() const;

private:
#if defined(_WIN32)
     CertificateGuiSearch certificateSearch_;
#endif
     std::vector<BYTE> message_;
     std::vector<BYTE> detachedSignature_;
};


#endif // sign_message_h__
