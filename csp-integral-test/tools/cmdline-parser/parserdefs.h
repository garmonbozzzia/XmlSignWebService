/// @file
/// @brief Файл содержит определения служебных типов для анализатора командной строки.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef CMDLINEPARSER_DEFS_H
#define CMDLINEPARSER_DEFS_H

#include <list>
#include <string>
#include <exception>

namespace cmdlineparser
{
	typedef std::list< std::string > Args;

	namespace exception
	{
		class Base: public std::exception{};
		class NeedHelp: public Base{};
		class ErrFlagAlreadySet: public Base{};
		class ErrBadArgs: public Base{};
		class NoArgs: public Base{};
	}
}

#endif // CMDLINEPARSER_DEFS_H