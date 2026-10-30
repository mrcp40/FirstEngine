#include "Precompiled.h"
#include "FirstEngine.h"

FirstEngine::App& FirstEngine::MainApp()
{
	static App sApp;
	return sApp;
}