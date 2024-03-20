#include <iostream>
#include <tchar.h>
#include <windows.h>

using namespace std;

#define NUM_THREADS 4

//typedef unsigned int        UINT;
unsigned int count = 0;

//typedef unsigned long       DWORD;
//#define WINAPI      __stdcall
//typedef void far* LPVOID; // far(?) lp(?)
//typedef CONST void far* LPCVOID;

DWORD WINAPI ThreadProc(LPVOID IpParam) //쓰레드 프로세스
{
    for (UINT i = 0; i < 10000; ++i)
    {
        ++*((int*)IpParam);
    }
    return 0;
}



int main()
{
    DWORD dwThreadId[NUM_THREADS];
    HANDLE hThread[NUM_THREADS];
    
    unsigned int count = 0;


    for (UINT i = 0; i < NUM_THREADS; i++)
    {
        hThread[i] = CreateThread(
            nullptr,           // 기본 보안 속성
            0,                 // 기본 스택 사이즈
            ThreadProc,        // 쓰레드 함수
            (void*)&count,     // 쓰레드 함수의 매개변수 인자
            0,                 // default 생성 flag
            &dwThreadId[i]     // 쓰레드 전달받기 위한 ID
        );
    }

    WaitForMultipleObjects(NUM_THREADS, hThread, TRUE, INFINITE);

    _tprintf(_T("Count : %d\n"), count); // wprintf

    for (UINT i = 0; i < NUM_THREADS; i++)
    {
        CloseHandle(hThread[i]);
    }
    return 0;
}
