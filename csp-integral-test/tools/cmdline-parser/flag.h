/// @file
/// @brief Файл содержит определение класса флага командной строки.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef CMDLINEPARSER_FLAG_H
#define CMDLINEPARSER_FLAG_H

#include <assert.h>
#include <ostream>
//#include <boost/shared_ptr.hpp>
#include "parserdefs.h"

namespace cmdlineparser{

namespace flag{


class IFlagImpl{
public:
     virtual const char * GetName() const  = 0;
     virtual const char * GetFlag() const = 0;
     virtual bool IsOptional() const = 0;
     virtual const char * GetDescription() const = 0;
     virtual bool IsAlreadySet() const = 0;
     virtual void SetDefault() = 0;
     virtual void Parse( Args & args ) = 0;
     virtual std::ostream& PrintHelp( std::ostream& s ) const = 0; 
};

template< class ValType >
class FlagImpl: public IFlagImpl
{
public:
     // реализация интерфейса IFlagImpl
     virtual const char * GetName() const{ return name_.c_str(); }
     virtual const char * GetFlag() const{ return flag_.c_str(); }
     virtual bool IsOptional() const{ return optional_; }
     virtual const char * GetDescription() const{ return description_.c_str(); }
     virtual bool IsAlreadySet() const{ return isAlreadySet_; }
     virtual void SetDefault(){ val_ = defVal_; }
     // необходимо специализировать
     virtual void Parse( Args & args ); 
     // при необходимости специализировать
     virtual std::ostream& PrintHelp( std::ostream& s ) const
	 { 
		 s<<std::boolalpha;
		 s<<flag_<<"\t"<<name_<<"\t\t\tdef: "<<defVal_<<"\n";
		 return s;
	 }

public:
     FlagImpl( 
          const char * name,
          const char * flag,
          const ValType & defVal,
          bool opt = true,
          const char* descr = NULL
     ):
     name_( name ),
     flag_( flag ),
     defVal_( defVal ),
     optional_( opt ),
     description_( (descr? descr : " ") ), 
     val_( defVal ),
     isAlreadySet_( false )
     {}
     const ValType & GetVal() const{ return val_; }
private:
     FlagImpl();
     void SetVal( const ValType & val ){ val_ = val; }
     void SetIsAlreadySet()
	 { 
		 if( IsAlreadySet() )
			 throw exception::ErrBadArgs(); 
		 isAlreadySet_ = true; 
	 }

private:
     const std::string name_;
     const std::string flag_;
     const ValType defVal_;
     const bool optional_;
     const std::string description_;
     // значение
     ValType val_;
     bool isAlreadySet_;
};

//////////////////////////////////////////////////////////////////////////
// интерфейс для флагов

class IFlag
{
public:
//      virtual const char * GetFlag() const = 0;
//      virtual bool IsSet() const = 0;
     virtual std::ostream& PrintHelp( std::ostream& s ) const = 0;
     virtual IFlagImpl* GetImplIface() const = 0;
};

//////////////////////////////////////////////////////////////////////////
// шаблон для флагов

template <class ValType>
class Flag: public IFlag
{
public:
     // реализация интерфейса IFlag
     virtual IFlagImpl* GetImplIface() const{ return impl_; }
     // при необходимости специализировать
     std::ostream& PrintHelp( std::ostream& s ) const{ return impl_->PrintHelp( s ); }

public:
	Flag( 
		const char * name,
		const char * flag,
		const ValType & defVal,
		bool opt = true,
		const char* descr = NULL 
		):
	impl_( new FlagImpl<ValType>( name, flag, defVal, opt, descr ))
	{
	}
	~Flag(){ 
		delete impl_; 
	}
	const char * GetName() const{ return impl_->GetName(); }
	const char * GetFlag() const{ return impl_->GetFlag(); }
     bool IsOptional() const{ return impl_->IsOptional(); }
     const char * GetDescription() const{ return impl_->GetDescription(); }
     bool IsSet() const{ return impl_->IsAlreadySet(); }
	 void SetDefault(){ impl_->SetDefault(); }
     // необходимо специализировать
     void Parse( Args & args ){ impl_->Parse( args ); } 
     const ValType & GetVal() const{ return impl_->GetVal(); }
private:
     Flag();
     
private:
     // свойства
     FlagImpl<ValType>* impl_;
};

std::ostream& operator<<( std::ostream& s, const flag::IFlagImpl * flag );
std::ostream& operator<<( std::ostream& s, const flag::IFlag * flag );

} // namespace flag
using flag::Flag;

} // namespace cmdlineparser

#endif //CMDLINEPARSER_FLAG_H