#include <FirstEngine/Inc/FirstEngine.h>
#include "DoSomethingState.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	FirstEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	FirstEngine::App& myApp = FirstEngine::MainApp();
	myApp.AddState<DoSomethingState>("DoSomethingState");
	myApp.Run(config);


	return 0;
}