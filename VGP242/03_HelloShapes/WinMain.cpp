#include <FirstEngine/Inc/FirstEngine.h>
#include "DoSomethingState.h"
#include "DoColorState.h"
#include "ThirdShapeColor.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	FirstEngine::AppConfig config;
	config.appName = L"Hello Shapes";

	FirstEngine::App& myApp = FirstEngine::MainApp();
	myApp.AddState<DoSomethingState>("DoSomethingState");
	myApp.AddState<DoColorState>("DoColorState");
	myApp.AddState<ThirdShapeColorState>("ThirdShapeState");
	myApp.Run(config);


	return 0;
}