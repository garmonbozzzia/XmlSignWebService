/// @file
/// @brief Файл содержит определение методов интегрального класса тестов и необходимых ему функторов.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#include "stdafx.h"
#include "integral-test.h"


struct run_test: public std::unary_function< TestBase*, void >
{
     result_type operator()( argument_type _test ){
          _test->SafeRun();
     }
};

struct delete_test: public std::unary_function< TestBase*, void >
{
     result_type operator()( argument_type _test ){
          delete _test;
          _test = 0;
     }
};



IntegralTest::IntegralTest( const Settings& _settings )
: settings_( _settings )
{

}

IntegralTest::~IntegralTest()
{
     std::for_each( testList_.begin(), testList_.end(), delete_test() );
}

void IntegralTest::Run()
{
     std::for_each( testList_.begin(), testList_.end(), run_test() );
}


void IntegralTest::AddTest( TestBase* _newTest )
{
     if( !_newTest )
          throw std::invalid_argument( "IntegralTest::AddTest" );

     _newTest->SetSettings( &settings_ );
     testList_.push_back( _newTest );
}

