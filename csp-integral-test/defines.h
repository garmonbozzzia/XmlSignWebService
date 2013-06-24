/// @file
/// @brief Файл содержит служебные определения.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef defines_h__
#define defines_h__

#include <string>

#if defined(_WIN32)
#include <tchar.h>
#else
#include "platform_pack/platform.h"
#if defined(_UNICODE) || defined(UNICODE)
#include <wchar.h>
#define TCHAR wchar_t
#else
#define TCHAR char
#endif //  defined(_UNICODE) || defined(UNICODE)
#endif //  defined(_WIN32)

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

typedef std::basic_string< TCHAR > tstring;

typedef DWORD ErrorCode;

#endif // defines_h__
