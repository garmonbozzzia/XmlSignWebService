/// @file
/// @brief Файл содержит определение класса исключения для обработки ошибок возникающих при работе с криптопровайдером.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef csp_exception_h__
#define csp_exception_h__


#include <string>
#include <exception>


class csp_exception: public std::exception
{
public:
     csp_exception( const char* _function, ErrorCode _code )
          : code_( _code )
     {
          std::ostringstream sream;
          sream << _function;
          sream << " returns error = ";
          sream << std::hex << _code;
          message_ = sream.str();
    }
    
    virtual const char* what() const throw () {
	return message_.c_str();
    }
     
    ErrorCode code() const { 
	return code_;
    }
     
    virtual ~csp_exception () throw () {
    }

private:
    std::string message_;
    ErrorCode code_;
};

#if defined(__unix__)

class string_exception: public std::exception {
private:
    char *m;
public:
    string_exception(const char* msg) throw() {
	m = new char[strlen(msg)+1];
	strcpy(m, msg);
    }
    
    string_exception(const string_exception& s) throw() {
	m = new char[strlen(s.m)+1];
	strcpy(m, s.m);
    }

    virtual ~string_exception() throw () {
	delete m;
    }
    
    string_exception& operator= (const string_exception& s) throw() {
	if(&s != this) { // prevent self-assignment
	    delete m;
	    m = new char[strlen(s.m)+1];
	    strcpy(m, s.m);
	}
    }

    virtual const char* what() const throw() {
	return m;
    }
};

#endif // defined(__unix__)


#endif // csp-exception_h__