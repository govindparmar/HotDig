#pragma once
#include <Windows.h>
#include <strsafe.h>
#include <sal.h>

#define EXTERN extern

typedef struct _HOTKEY
{
	WCHAR wszPath[MAX_PATH];
	WCHAR wszDirectory[MAX_PATH];
	WCHAR wszArguments[500U];
	WCHAR wszVerb[10];
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
