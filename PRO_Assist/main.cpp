﻿#define _CRT_SECURE_NO_WARNINGS
#include "Discord_Headers/discord_main.h"
bool isRunning(LPCSTR pName){
	//--Converting pName to LPCWSTR--//
	USES_CONVERSION;
	LPCSTR pNameDef = pName;
	LPCWSTR pNewName = A2W(pNameDef);
	//--Converting pName to LPCWSTR--//
	HWND hwnd;
	hwnd = FindWindow(NULL, pNewName);
	if (hwnd != 0) {
		return true;
	}
	else {
		return false;
	}
}
static void discordInit() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}
static void updateDiscordPresence(){
	if (SendPresence){
		DiscordRichPresence discordPresence;
		memset(&discordPresence, 0, sizeof(discordPresence));
		discordPresence.state = "Join the revolution!";
		discordPresence.largeImageKey = "1-big";
		discordPresence.smallImageKey = "1-small";
		discordPresence.largeImageText = "Pokemon Revolution Online";
		discordPresence.smallImageText = "site: pokemonrevolution.net";
		discordPresence.details = "";
		discordPresence.startTimestamp = StartTime;
		discordPresence.endTimestamp = 0;
		discordPresence.partyId = "";
		discordPresence.partySize = 0;
		discordPresence.partyMax = 0;
		discordPresence.matchSecret = "";
		discordPresence.joinSecret = "";
		discordPresence.spectateSecret = "";
		discordPresence.instance = 0;
		Discord_UpdatePresence(&discordPresence);
	}
	else {
		Discord_ClearPresence();
	}
}
static void DiscordLoop(){
	StartTime = time(0);
	while(SendPresence){
		if(!isRunning("Pokemon Revolution")) {
			SendPresence = 0;
			break;
		}
		else{
			Sleep(1500);
			updateDiscordPresence();
		}
		#ifdef DISCORD_DISABLE_IO_THREAD
			Discord_UpdateConnection();
		#endif
		Discord_RunCallbacks();
	}
}
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow){
	//----------------Set Proccess Thread Pointers----------------//
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	//--------------Convert Proccess Name TO LPWSTR--------------//
	char proccess[] = "PRO32.exe";
	wchar_t wProccess[10];
	mbstowcs(wProccess, proccess, strlen(proccess) + 1);
	LPWSTR ptrProccess = wProccess;
	//-----------------Create the PRO Proccess!-----------------//
	CreateProcess(NULL, ptrProccess, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	//-----------------Start Discord RP's Loop-----------------//
	Sleep(1500);
	discordInit();
	DiscordLoop();
	Discord_Shutdown();
	return 0;
}
