#include "MindEyeTimer.h"

DWORD WINAPI MindEyeTimer::ThreadProc(ThreadProcParam* pThreadProcParam)
{
	// 事件名称 MindEyeTimer进程id_线程id
	CHAR eventName[MAX_PATH] = "";
	DWORD dwProcessId = ::GetCurrentProcessId();
	DWORD dwThreadId = ::GetCurrentThreadId();
	sprintf_s(eventName, MAX_PATH, "MindEyeTimer%08X_%08X", dwProcessId, dwThreadId);
	HANDLE hEvent = ::CreateEventA(NULL, FALSE, FALSE, eventName);
	if (hEvent == NULL)
	{
		return -1;
	}
	LPTHREAD_START_ROUTINE lpStartAddress = pThreadProcParam->lpStartAddress;
	LPVOID lpParameter = pThreadProcParam->lpParameter;
	DWORD dwCycles = pThreadProcParam->dwCycles;
	TimerProcParam* pTimerProcParam = new TimerProcParam();
	pTimerProcParam->dwInterval = pThreadProcParam->dwInterval;
	pTimerProcParam->dwThreadId = dwThreadId;
	HANDLE handle = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)TimerProc, pTimerProcParam, NULL, NULL);
	if (handle == NULL)
	{
		return -1;
	}
	while (dwCycles > 0)
	{
		::WaitForSingleObject(hEvent, INFINITE);
		lpStartAddress(lpParameter);
		if (dwCycles != INFINITE)
		{
			dwCycles--;
		}
	}
	::CloseHandle(hEvent);
	delete pThreadProcParam;
	return 0;
}

DWORD WINAPI MindEyeTimer::TimerProc(TimerProcParam* pTimerProcParam)
{
	CHAR eventName[MAX_PATH] = "";
	DWORD dwProcessId = ::GetCurrentProcessId();
	sprintf_s(eventName, MAX_PATH, "MindEyeTimer%08X_%08X", dwProcessId, pTimerProcParam->dwThreadId);
	HANDLE hEvent = ::OpenEventA(EVENT_ALL_ACCESS, TRUE, eventName);
	if (hEvent == NULL)
	{
		return -1;
	}
	DWORD dwFlags = 0;
	while (GetHandleInformation(hEvent, &dwFlags))
	{
		Sleep(pTimerProcParam->dwInterval);
		::SetEvent(hEvent);
	}
	delete pTimerProcParam;
	return 0;
}

HRESULT MindEyeTimer::setTimeOut(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwInterval, DWORD dwCycles)
{
	ThreadProcParam* pThreadProcParam = new ThreadProcParam();
	pThreadProcParam->lpStartAddress = lpStartAddress;
	pThreadProcParam->lpParameter = lpParameter;
	pThreadProcParam->dwInterval = dwInterval;
	pThreadProcParam->dwCycles = dwCycles;
	HANDLE handle = ::CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ThreadProc, pThreadProcParam, NULL, NULL);
	if (handle == NULL)
	{
		return ::GetLastError();
	}
	return S_OK;
}
