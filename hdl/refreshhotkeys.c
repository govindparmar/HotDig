#include "HDL.h"

#define KEY_FORMAT L"SOFTWARE\\GovindParmar\\HotDig\\%I32d"

_Ret_range_(FALSE, TRUE)
_Check_return_
_Success_(return)

BOOL WINAPI RefreshHotkeys()
{
	HKEY hKey = NULL;
	LSTATUS ls;
	WCHAR wszKey[50];
	INT i;
	DWORD dwCB;

	for (i = 0; i <= 9; i++)
	{
		StringCchPrintfW(wszKey, 50, KEY_FORMAT, i);
		ls = RegOpenKeyExW(HKEY_CURRENT_USER, wszKey, 0, KEY_READ, &hKey);
		if (ls != ERROR_SUCCESS)
		{
			goto cleanup;
		}

		dwCB = MAX_PATH * sizeof(WCHAR);
		ls = RegQueryValueExW(hKey, L"Path", NULL, NULL, (LPBYTE)g_Hotkeys[i].wszPath, &dwCB);
		if (ls != ERROR_SUCCESS)
		{
			goto cleanup;
		}

		// 0: Disabled
		// 1: ShellExecuteW
		// 2: CreateProcessW
		// 3: _wsystem
		dwCB = sizeof(DWORD);
		ls = RegQueryValueExW(hKey, L"CallType", NULL, NULL, (LPBYTE)&g_Hotkeys[i].dwCallType, &dwCB);
		if (ls != ERROR_SUCCESS)
		{
			goto cleanup;
		}

		dwCB = MAX_PATH * sizeof(WCHAR);
		ls = RegQueryValueExW(hKey, L"Directory", NULL, NULL, (LPBYTE)g_Hotkeys[i].wszDirectory, &dwCB);
		if (ls != ERROR_SUCCESS)
		{
			goto cleanup;
		}

		if (HOTKEY_ENTRY_CALL_CREATEPROCESSW == g_Hotkeys[i].dwCallType)
		{
			dwCB = 499 * sizeof(WCHAR);
			g_Hotkeys[i].wszArguments[0] = L' ';
			ls = RegQueryValueExW(hKey, L"Arguments", NULL, NULL, (LPBYTE) (g_Hotkeys[i].wszArguments + 1), &dwCB);
		}
		else
		{
			dwCB = 500 * sizeof(WCHAR);
			ls = RegQueryValueExW(hKey, L"Arguments", NULL, NULL, (LPBYTE) g_Hotkeys[i].wszArguments, &dwCB);
		}
		if (ls != ERROR_SUCCESS)
		{
			goto cleanup;
		}


		dwCB = 10 * sizeof(WCHAR);
		ls = RegQueryValueExW(hKey, L"Verb", NULL, NULL, (LPBYTE)g_Hotkeys[i].wszVerb, &dwCB);
		if (ls != ERROR_SUCCESS)
		{
			goto cleanup;
		}
	}

	ls = ERROR_SUCCESS;
cleanup:
	if (hKey != NULL)
	{
		RegCloseKey(hKey);
	}
	return ERROR_SUCCESS == ls;
}
