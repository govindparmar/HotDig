#pragma once
#include <Windows.h>
#include <strsafe.h>
#include <sal.h>

#define EXTERN extern
#define HOTKEY_ENTRY_DISABLED 0
#define HOTKEY_ENTRY_CALL_SHELLEXECUTEW 1
#define HOTKEY_ENTRY_CALL_CREATEPROCESSW 2
#define HOTKEY_ENTRY_CALL__WSYSTEM 3
#define WSYSTEM_STRING_CCH (MAX_PATH + MAX_PATH + 510)

typedef struct _HOTKEY
{
	WCHAR wszPath[MAX_PATH];
	WCHAR wszDirectory[MAX_PATH];
	WCHAR wszArguments[500U];
	WCHAR wszVerb[10];
	DWORD dwCallType;
} HOTKEY, *PHOTKEY;

BOOL APIENTRY DllMain(_In_ HINSTANCE hInstDLL, _In_ DWORD dwReason, _In_ LPVOID lpReserved);
LRESULT CALLBACK LowLevelKeyboardProc(_In_ INT nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

_Ret_range_(FALSE, TRUE)
_Check_return_
_Success_(return)

BOOL WINAPI RefreshHotkeys();

EXTERN CRITICAL_SECTION g_CS;
EXTERN BOOL g_fCtrl, g_fAlt;
EXTERN HOTKEY g_Hotkeys[10];
EXTERN WCHAR g_wszSystemCallString[WSYSTEM_STRING_CCH];

