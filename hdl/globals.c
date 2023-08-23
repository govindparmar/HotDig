#include "HDL.h"

CRITICAL_SECTION g_CS;
BOOL g_fCtrl, g_fAlt;
HOTKEY g_Hotkeys[10];
WCHAR g_wszSystemCallString[MAX_PATH + MAX_PATH + 500 + 2];
