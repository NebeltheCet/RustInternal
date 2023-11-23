#include <Windows.h>
#include <iostream>
#include "SDK/Utils/Dissector/Dissector.hpp"
#include "Hooks/Hooks.hpp"

void MainThread(HMODULE hModule) {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	Dissector::Attach();
	Hooks::Attach();

	while (!GetAsyncKeyState(VK_END))
		Sleep(100);

	Hooks::Detach();

	FreeConsole();
	//fclose(stdout);

	FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
}

int DllMain(HMODULE hModule, DWORD dwCallReason, LPVOID lpReserved) {
	if (dwCallReason == DLL_PROCESS_ATTACH) {
		HANDLE hThread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, nullptr);
		if (hThread) {
			CloseHandle(hThread);
		}
	}

	return TRUE;
}

