#include "mini_dump.h"

#include <cstdio>
#include <cstring>
#include <tchar.h>

// based on dbghelp.h : Dump된 정보를 가진다.
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)( HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
                                 CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                 CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                 CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam );

CDumper::CDumper()
{
      ::SetUnhandledExceptionFilter( TopLevelFilter );  //  ExceptionFilter에 함수 등록하기
}
CDumper::~CDumper(void)
{ }
 
// Exception이 나면 호출 됨
LONG CDumper::TopLevelFilter( struct _EXCEPTION_POINTERS* exceptioninfo )
{
           HMODULE hDll = ::LoadLibrary( TEXT("DBGHELP.DLL") );
           MINIDUMPWRITEDUMP pDump = ( MINIDUMPWRITEDUMP )::GetProcAddress( hDll, "MiniDumpWriteDump");
		   
		   TCHAR buf[512];
		   GetCurrentDirectory(512, buf);
		   _tcscat_s(buf, 512, TEXT("\\mem_dump.dmp"));
		   
		   _tprintf(TEXT("dumping memory to %s ...\n"), buf);

           // 덤프파일 생성
            HANDLE hFile = ::CreateFile( buf,
                                            GENERIC_WRITE, 
                                            FILE_SHARE_WRITE, 
                                            NULL, 
                                            CREATE_ALWAYS,
                                            FILE_ATTRIBUTE_NORMAL, NULL );
 
            // 덤프뜨기
            _MINIDUMP_EXCEPTION_INFORMATION   ExInfo;
            ExInfo.ThreadId    = ::GetCurrentThreadId();
            ExInfo.ExceptionPointers = exceptioninfo;
            ExInfo.ClientPointers  = NULL;
 
            // write the dump : 해당 typedef된 것으로 덤프만들기
            BOOL bOK = pDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );
            ::CloseHandle( hFile );   // 완성됨
 
			return 0;
}