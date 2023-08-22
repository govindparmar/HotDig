#include "HDL.h"

LRESULT CALLBACK LowLevelKeyboardProc(_In_ INT nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	KBDLLHOOKSTRUCT kbdhs = *(KBDLLHOOKSTRUCT *)lParam;
	if (nCode < 0)
	{
		goto cleanup;
	}

	if (WM_KEYDOWN == wParam || WM_SYSKEYDOWN == wParam)
	{
		switch (kbdhs.vkCode)
		{
		case VK_MENU:
		case VK_LMENU:
		case VK_RMENU:
			EnterCriticalSection(&g_CS);
			g_fAlt = TRUE;
			LeaveCriticalSection(&g_CS);
			break;
		case VK_CONTROL:
		case VK_LCONTROL:
		case VK_RCONTROL:
			EnterCriticalSection(&g_CS);
			g_fCtrl = TRUE;
			LeaveCriticalSection(&g_CS);
			break;

		}

		if (kbdhs.vkCode >= '0' && kbdhs.vkCode <= '9')
		{
			INT i = kbdhs.vkCode - '0';
			if (g_fAlt && g_fCtrl)
			{
				ShellExecuteW(NULL, g_Hotkeys[i].wszVerb,
					g_Hotkeys[i].wszPath, 
					g_Hotkeys[i].wszArguments,
					g_Hotkeys[i].wszDirectory, SW_SHOWNORMAL);
			}
		}
	}

	if (WM_KEYUP == wParam || WM_SYSKEYUP == wParam)
	{
		switch (kbdhs.vkCode)
		{
		case VK_MENU:
		case VK_LMENU:
		case VK_RMENU:
			EnterCriticalSection(&g_CS);
			g_fAlt = FALSE;
			LeaveCriticalSection(&g_CS);
			break;
		case VK_CONTROL:
		case VK_LCONTROL:
		case VK_RCONTROL:
			EnterCriticalSection(&g_CS);
			g_fCtrl = FALSE;
			LeaveCriticalSection(&g_CS);
			break;
		}

	}

cleanup:
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
