/// @file
/// @brief Прекомпилируемый заголовок.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.

#ifndef stdafx_h__
#define stdafx_h__

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


#include "targetver.h"

#include <stdio.h>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <fstream>
#include <iterator>
#include <list>
#include <algorithm>
#include <iostream>

#if defined(_WIN32)
#include <tchar.h>
#include <windows.h>
#include <WinCrypt.h>
#else
#include "platform_pack/platform.h"
void  SetLastError( DWORD error );
DWORD GetLastError(void);
#endif

#include "defines.h"
#include "csp-defines/itccspdefs.h"
#include "tools/csp-exception.h"
#include "tools/settings.h"


#endif // stdafx_h__
