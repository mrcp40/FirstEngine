#include <FirstEngine/Inc/FirstEngine.h>
#include "MainState.h"
#include "GameState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	FirstEngine::AppConfig config;
	config.appName = L"Hello App State";

	FirstEngine::App& myApp = FirstEngine::MainApp();
	myApp.AddState<MainState>("MainState");
	myApp.AddState<GameState>("GameState");

	myApp.Run(config);

	return 0;
}