#include "pch.h"
#include "Timer.h"

void MainTimer()
{
    HANDLE hEvent = ::CreateEvent(NULL, FALSE, FALSE, L"IsaacMainTimer");
    while (true)
    {
        ::SetEvent(hEvent);
        ::Sleep(1000);
    }
    ::CloseHandle(hEvent);
}
