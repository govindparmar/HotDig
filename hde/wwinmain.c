#include <Windows.h>
#include <sal.h>

CONST WCHAR g_wszClassName[] = L"HOT_DIGITS_LOADER_WINDOW_CLASS_MO";

INT APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ INT nShowCmd
)
{
	HINSTANCE hInstDLL = NULL;
	HOOKPROC hpLLKP = NULL;
	HHOOK hHook = NULL;
	HWND hWnd;
	MSG Msg;
	WNDCLASSEXW wcex;

	ZeroMemory(&wcex, sizeof(WNDCLASSEXW));
	hInstDLL = LoadLibraryW(L"HDL.dll");
	if (NULL == hInstDLL)
	{
		return (INT)GetLastError();
	}

	hpLLKP = (HOOKPROC)GetProcAddress(hInstDLL, "LowLevelKeyboardProc");
	if (NULL == hpLLKP)
	{
		return (INT)GetLastError();
	}
	
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.hInstance = hInstance;
	wcex.lpszClassName = g_wszClassName;
	wcex.lpfnWndProc = DefWindowProcW;
	if (!RegisterClassExW(&wcex))
	{
		return (INT)GetLastError();
	}


	hWnd = CreateWindowW(g_wszClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		return (INT)GetLastError();
	}

	hHook = SetWindowsHookExW(WH_KEYBOARD_LL, hpLLKP, hInstDLL, 0);
	while (GetMessageW(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}
	UnhookWindowsHookEx(hHook);
	FreeLibrary(hInstDLL);
	return (INT)Msg.wParam;
}
