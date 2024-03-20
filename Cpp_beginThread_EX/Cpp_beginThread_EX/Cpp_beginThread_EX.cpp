#include <iostream>
#include <process.h>
#include <windows.h>
#include <string.h>

using namespace std;

void ErrorHandling(char* message);
unsigned WINAPI ThreadFunc1(void* arg);
unsigned WINAPI ThreadFunc2(void* arg);
unsigned WINAPI ThreadFunc3(void* arg);

HANDLE create(void* security,
    unsigned stack_size,
    unsigned (*start_address)(void*),
    void* arglist,
    unsigned initflag,
    unsigned* thrdaddr);
void InvalidThreadCheck(HANDLE hthread);
void WaitTheadCheck(HANDLE hthread, DWORD dwMilliseconds);



#define THREAD_COUNT 3

int main()
{

    HANDLE hthread[THREAD_COUNT];
    unsigned threadID;
    int param = 100;

    
    hthread[0] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc1, (void*)&param, 0, &threadID);
    hthread[1] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc2, (void*)&param, 0, &threadID);
    hthread[2] = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc3, (void*)&param, 0, &threadID);

    WaitTheadCheck(hthread[0], INFINITE);
    WaitTheadCheck(hthread[1], INFINITE);
    WaitTheadCheck(hthread[2], INFINITE);
    
    
    cout << "end of main" << endl;


    return 0;

}

void InvalidThreadCheck(HANDLE hthread)
{
    if (hthread == 0)
    {
        char* message = (char*)"_beginthreadex() error";
        ErrorHandling(message);
        return;
    }

}

void WaitTheadCheck(HANDLE hthread, DWORD dwMilliseconds)
{
    DWORD wr;
    if ((wr = WaitForSingleObject(hthread, INFINITE)) == WAIT_FAILED)
    {
        ErrorHandling((char*)"thread wait error");
        return;
    }

    cout << "wait result : ";
    if (wr == WAIT_OBJECT_0)
    {
        cout << "signaled" << endl;
    }
    else
    {
        cout << "time-out" << endl;
    }
}
HANDLE create(void* security,
    unsigned stack_size,
    unsigned (*func)(void*),
    void* arglist,
    unsigned initflag,
    unsigned* thrdaddr)
{
    HANDLE hthread = (HANDLE)_beginthreadex(security, stack_size, func, arglist, initflag, thrdaddr);
    InvalidThreadCheck(hthread);

    return hthread;
}

unsigned WINAPI ThreadFunc1(void* arg)
{
    int cnt = *((int*)arg); //void* => int*  => casting
    for (int i = 0; i < cnt; i++)
    {
        Sleep(100);
        cout << "**                 **                  **                  **" << endl;
    }

    return 0;
}


unsigned WINAPI ThreadFunc2(void* arg)
{
    int cnt = *((int*)arg); //void* => int*  => casting
    for (int i = 0; i < cnt; i++)
    {
        Sleep(100);
        cout << "   **   **   **   **" << endl;
    }

    return 0;
}


unsigned WINAPI ThreadFunc3(void* arg)
{
    int cnt = *((int*)arg); //void* => int*  => casting
    for (int i = 0; i < cnt; i++)
    {
        Sleep(100);
        cout << "       **       **       **       **" << endl;
    }

    return 0;
}





void ErrorHandling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

//stderr




//**
//**
//**      **
//**
//        **
//                **
//**
//        **
