/// @file
/// @brief Файл содержит определение методов класса флага командной строки.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "flag.h"

namespace cmdlineparser{

namespace flag{

template<>
void FlagImpl<int>::Parse( Args & args )
{
     for( Args::iterator arg = args.begin(); arg != args.end(); ++arg )
     {
          if( !arg->compare( GetFlag() ))
          {
               if( IsAlreadySet() ) // если флаг задан( уже встречался среди переданных аргументов )
				   throw exception::ErrBadArgs();
               Args::iterator flag = arg; // первый аргумент - флаг
               Args::iterator opt = ++arg; // следущий за ним аргумент - опция 
               if( opt == args.end() )
                    throw exception::ErrBadArgs();
               SetVal( atoi( opt->c_str() ));
               SetIsAlreadySet(); // выставляем признак того, что данный флаг уже задан( защита от дублирования )
               // удаляем из списка аргументов считанные флаг и опцию
               args.erase( flag ); 
               args.erase( opt );
               break;
          }
     }
}

template<>
void FlagImpl<std::string>::Parse( Args & args )
{
     for( Args::iterator arg = args.begin(); arg != args.end(); ++arg )
     {
          if( !arg->compare( GetFlag() ))
          {
               if( IsAlreadySet() ) // если флаг задан( уже встречался среди переданных аргументов )
                    throw exception::ErrBadArgs();
               Args::iterator flag = arg; // первый аргумент - флаг
               Args::iterator opt = ++arg; // следущий за ним аргумент - опция 
               if( opt == args.end() )
                    throw exception::ErrBadArgs();
               SetVal( *opt );
               SetIsAlreadySet(); // выставляем признак того, что данный флаг уже задан( защита от дублирования )
               // удаляем из списка аргументов считанные флаг и опцию
               args.erase( flag ); 
               args.erase( opt );
               break;
          }
     }
}

template<>
void FlagImpl<bool>::Parse( Args & args )
{
     for( Args::iterator arg = args.begin(); arg != args.end(); ++arg )
     {
          if( !arg->compare( GetFlag() ))
          {
               if( IsAlreadySet() ) // если флаг задан( уже встречался среди переданных аргументов )
                    throw exception::ErrBadArgs();
               // аргумент, являющийся булевым флагом, не предполагает следующей за ним опции
               SetVal( true ); 
               SetIsAlreadySet(); // выставляем признак того, что данный флаг уже задан( защита от дублирования )
               // удаляем из списка аргументов считанный флаг
               args.erase( arg ); 
               break;
          }
     }
}

std::ostream& operator<<( std::ostream& s, const flag::IFlagImpl * flag )
{
     return flag->PrintHelp( s );
}

std::ostream& operator<<( std::ostream& s, const flag::IFlag * flag )
{
     return flag->PrintHelp( s );
}

} // namespace flag

} // namespace cmdlineparser{
