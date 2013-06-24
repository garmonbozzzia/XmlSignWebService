/// @file
/// @brief Файл содержит определение класса настроек интегрального теста.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef settings_h__
#define settings_h__


#include "cmdline-parser/cmdline-parser.h"
#include "provider-info.h"
#include "icsp-wrapper.h"
#if defined(_WIN32)
#include "capi-csp-wrapper.h"
#endif
#include "csp-direct-call.h"


class Settings
{
	typedef cmdlineparser::Flag<tstring> LogFlag;
	typedef cmdlineparser::Flag<tstring> ContainerFlag;
	typedef cmdlineparser::Flag<tstring> MessageFlag;
     typedef cmdlineparser::Flag<int> IterationsNumFlag;
     typedef cmdlineparser::Flag<bool> CspCallStrategyFlag;

public:
     Settings( const CmdLineInput& _cmd, const ProviderInfo& _provInfo );
     ~Settings(){}
     
     const ProviderInfo& ProvInfo() const;
     LPCTSTR Container() const; 
     std::ostream& LogStream() const;
     LPCTSTR MessageFile() const;
     int IterationNum() const;
     ICspWrapper* csp()const { return csp_; }

private:
     void ParseCmdLine( const CmdLineInput& _cmd );

     void SetCspCallStrategy( const CspCallStrategyFlag& _cspDirectCallFlag );
     void SetLogStream( const LogFlag& _flag );
     void SetMessageFile( const MessageFlag& _flag );
     void SetContainer( const ContainerFlag& _flag );
     void SetIterationsNum( const IterationsNumFlag& _flag );

private:
     ProviderInfo providerInfo_;     

     tstring messageFile_;
     tstring container_;
     int iterationsNum_;
     ICspWrapper* csp_;

     mutable std::ostream* logStream_;
     std::ofstream logFile;
};


#endif // settings_h__
