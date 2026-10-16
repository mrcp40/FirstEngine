#include <FirstEngine/Inc/FirstEngine.h>

using namespace FirstEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;


	App myApp;
	myApp.Run(config);

	return 0;
}