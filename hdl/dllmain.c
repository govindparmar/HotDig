#include "HDL.h"

BOOL APIENTRY DllMain(_In_ HINSTANCE hInstDLL, _In_ DWORD dwReason, _In_ LPVOID lpReserved)
{
	if (DLL_PROCESS_ATTACH == dwReason)
	{
		(VOID) RefreshHotkeys();
		return InitializeCriticalSectionAndSpinCount(&g_CS, 0x00000400U);

	}
	else if (DLL_PROCESS_DETACH == dwReason)
	{
		DeleteCriticalSection(&g_CS);
	}

	return TRUE;
}
