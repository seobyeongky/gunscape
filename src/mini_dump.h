#pragma once

#include <Windows.h>
#include <dbghelp.h>

class CDumper
{
public:
	CDumper();
	~CDumper(void);
 
	static LONG WINAPI TopLevelFilter( struct _EXCEPTION_POINTERS* exceptioninfo );
};