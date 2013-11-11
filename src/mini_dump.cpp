#include "mini_dump.h"

#include <cstdio>
#include <cstring>
#include <tchar.h>

// based on dbghelp.h : Dump�� ������ ������.
typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)( HANDLE hProcess, DWORD dwPid, HANDLE hFile, MINIDUMP_TYPE DumpType,
                                 CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
                                 CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
                                 CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam );

CDumper::CDumper()
{
      ::SetUnhandledExceptionFilter( TopLevelFilter );  //  ExceptionFilter�� �Լ� ����ϱ�
}
CDumper::~CDumper(void)
{ }
 
// Exception�� ���� ȣ�� ��
LONG CDumper::TopLevelFilter( struct _EXCEPTION_POINTERS* exceptioninfo )
{
           HMODULE hDll = ::LoadLibrary( TEXT("DBGHELP.DLL") );
           MINIDUMPWRITEDUMP pDump = ( MINIDUMPWRITEDUMP )::GetProcAddress( hDll, "MiniDumpWriteDump");
		   
		   TCHAR buf[512];
		   GetCurrentDirectory(512, buf);
		   _tcscat_s(buf, 512, TEXT("\\mem_dump.dmp"));
		   
		   _tprintf(TEXT("dumping memory to %s ...\n"), buf);

           // �������� ����
            HANDLE hFile = ::CreateFile( buf,
                                            GENERIC_WRITE, 
                                            FILE_SHARE_WRITE, 
                                            NULL, 
                                            CREATE_ALWAYS,
                                            FILE_ATTRIBUTE_NORMAL, NULL );
 
            // �����߱�
            _MINIDUMP_EXCEPTION_INFORMATION   ExInfo;
            ExInfo.ThreadId    = ::GetCurrentThreadId();
            ExInfo.ExceptionPointers = exceptioninfo;
            ExInfo.ClientPointers  = NULL;
 
            // write the dump : �ش� typedef�� ������ ���������
            BOOL bOK = pDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpNormal, &ExInfo, NULL, NULL );
            ::CloseHandle( hFile );   // �ϼ���
 
			return 0;
}