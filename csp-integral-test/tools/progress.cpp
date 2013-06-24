/// @file
/// @brief Файл содержит определение методов класса отображение прогресса.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "progress.h"


const int ConsoleProgress::PROGRESS_STEPS_NUM = 10;

const char ConsoleProgress::PROGRESS_CHAR = '.';


ConsoleProgress::ConsoleProgress( std::ostream& _outStream )
: outStream_( _outStream )
, min_( 0 )
, max_( 100 )
, current_( min_ )
{

}


void ConsoleProgress::setRange( int _min, int _max )
{
     assert( _min < _max && _min == 0 );
     min_ = _min;
     max_ = _max;
}


void ConsoleProgress::getRange( int& _min, int& _max ) const
{
     _min = min_;
     _max = max_;
}


void ConsoleProgress::setProgress( int _val )
{
     assert( _val >= min_ && _val <= max_ );
     int step = ( max_ - min_ )/ PROGRESS_STEPS_NUM;
     if( _val % step == 0 )
          outStream_ << PROGRESS_CHAR;

     current_ = _val;
}


int ConsoleProgress::getProgress() const
{
     return current_;
}