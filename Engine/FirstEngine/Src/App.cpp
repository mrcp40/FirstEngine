#include "Precompiled.h"'
#include "App.h"
#include "AppState.h"

using namespace FirstEngine;
using namespace FirstEngine::Core;
using namespace FirstEngine::Graphics;

void App::Run(const AppConfig& config)
{
	LOG("App Start");

	// 初始化所有单例模式实例 (static initialize)
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);

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
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}

void App::Quit()
{
	mIsRunning = false;
}

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
}