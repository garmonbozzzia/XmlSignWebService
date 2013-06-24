/// @file
/// @brief ‘айл содержит определение класса, тестирующего работу в многопоточном режиме.
///
/// Copyright (c) InfoTeCS. All Rights Reserved.
#ifndef multithread_h__
#define multithread_h__

#include "../test-base.h"


/// @brief “естирует работу в многопоточном режиме.
class Multithread: public TestBase
{
public:
     /// @brief «апуск теста.
	virtual void Run();
};



namespace multithread_test_internal
{
     /// @brief —лужебна€ структура многопоточного теста.
	struct ThreadInfo
	{
		HANDLE handle;
		int threadNum;
		const Settings* parentSettings;
	};

     /// @brief —лужебный класс многопоточного теста.
	class ThreadSettingsBuilder
	{
	public:
		ThreadSettingsBuilder( ThreadInfo* info );
		~ThreadSettingsBuilder();
		const Settings* GetSettings() const{ return settings_; }
	private:
		tstring ThreadName() const;
	private:
		ThreadInfo* info_;
		Settings* settings_;
		tstring containerName_;
		tstring logName_;
	};

} // namespace multithread_test_internal

#endif // multithread_h__
