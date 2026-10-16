#include "Precompiled.h"'
#include "App.h"'

using namespace FirstEngine;

void App::Run(const AppConfig& config)
{
	LOG("App Start");

	// 初始化所有单例模式实例
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);

	// 初始化启动阶段

	// 更新
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
		{
			Quit();
			continue;
		}
	}

	LOG("App Is Terminating");
	// 终止最终阶段

	// 终止所有单例模式实例
	myWindow.Terminate();
}

void App::Quit()
{
	mIsRunning = false;
}