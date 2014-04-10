// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Debug.h"
#include "JoshoEngine.h"

JOSHO_C_API void wow_very_c()
{
	srand((unsigned int)time(NULL));
	int lol = rand() % 10000 + 100;
	printf("wow much love");

	while (true)
	{
		malloc(lol);

		lol++;
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		JoshoEngine::Debug::debugf("[JoshoEngine] Received process attach signal from OS.\n");
		break;
	case DLL_THREAD_ATTACH:
		JoshoEngine::Debug::debugf("[JoshoEngine] Received thread attach signal from OS.\n");
		break;
	case DLL_THREAD_DETACH:
		JoshoEngine::Debug::debugf("[JoshoEngine] Received thread detach signal from OS.\n");
		break;
	case DLL_PROCESS_DETACH:
		JoshoEngine::Debug::debugf("[JoshoEngine] Received process detach signal from OS.\n");
		break;
	}

	return TRUE;
}

