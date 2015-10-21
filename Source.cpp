#pragma comment(lib, "advapi32.lib")

#include<Windows.h>
#include<winerror.h>
#include<stdio.h>
#include <aclapi.h>
#include <tchar.h>
#include <iostream>
void main() {
	//Create structure of Waitable Timer
	//Define the parameters
	HANDLE hTimer = NULL, htTimer = NULL, hthTimer = NULL;
	LPSECURITY_ATTRIBUTES lpTimerAttributes = NULL;
	BOOL                  bManualReset = TRUE;
	LPCTSTR               lptTimerName = "fTimer";
	LPCTSTR               lpnTimerName = "nTimer";
	LPCTSTR               lpTimerName = NULL;
	//Transfer the parameters in function and create kernel object
	hTimer = CreateWaitableTimer(lpTimerAttributes, bManualReset, lpTimerName);
	//Test object for emptiness
	if (NULL == hTimer)
	{
		printf("CreateWaitableTimer failed (%d)\n", GetLastError());
		return;
	}
	else (printf("successful completion\n"));
	printf("timer = %d\n", hTimer);
	/****************************************************************************************/
	hthTimer = CreateWaitableTimer(lpTimerAttributes, bManualReset, lpTimerName);
	//Test object for emptiness
	if (NULL == hthTimer)
	{
		printf("CreateWaitableTimer failed (%d)\n", GetLastError());
		return;
	}
	else (printf("successful completion\n"));
	printf("timer = %d\n", hthTimer);
	/*************************named_object_of_kernel*******************************************/
	htTimer = CreateWaitableTimer(lpTimerAttributes, bManualReset, lptTimerName);
	if (NULL == htTimer)
	{
		printf("CreateWaitableTimer failed (%d)\n", GetLastError());
		return;
	}
	else (printf("successful completion\n"));
	//print result
	printf("timer = %d\n", htTimer);

	WORD dwDisposition = 0x1F0003;
	HANDLE newTimer;
	newTimer = OpenWaitableTimer(dwDisposition, bManualReset, lpnTimerName);

	printf("timer = %d\n", newTimer);
	/**************************************************************************************/


	LARGE_INTEGER liDueTime;
	liDueTime.QuadPart = -100000000LL;
	if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0))
	{
		printf("SetWaitableTimer failed (%d)\n", GetLastError());
		return;
	}
	if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)	printf("WaitForSingleObject failed (%d)\n", GetLastError());
	else printf("Timer was signaled.\n");

	STARTUPINFO siForNotepad = { sizeof(siForNotepad) };
	PROCESS_INFORMATION piForNotepad;
	TCHAR czCommandLine[] = "Notepad";
	CreateProcess(NULL, czCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &siForNotepad, &piForNotepad);

	if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0))
	{
		printf("SetWaitableTimer failed (%d)\n", GetLastError());
		return;
	}
	if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)	printf("WaitForSingleObject failed (%d)\n", GetLastError());
	else printf("Close process.\n");

	TerminateProcess(piForNotepad.hProcess, 0);
	/**************************************************************************************/
	VOID USBD_CloseHandle(HANDLE newTimer);
	VOID USBD_CloseHandle(HANDLE hTimer);
	VOID USBD_CloseHandle(HANDLE htTimer);
	return;
}