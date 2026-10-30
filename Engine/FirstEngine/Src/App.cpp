#include "Precompiled.h"'
#include "App.h"
#include "AppState.h"

using namespace FirstEngine;
using namespace FirstEngine::Core;
using namespace FirstEngine::Graphics;
using namespace FirstEngine::Input;

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
	InputSystem::StaticInitialize(handle);

	// 初始化启动阶段
	ASSERT(mCurrentState != nullptr, "App: no state is set");
	mCurrentState->Initialize();
	InputSystem* input = InputSystem::Get();

	// 更新
	mIsRunning = true;
	while (mIsRunning)
	{
		myWindow.ProcessMessage();
		input->Update();
		if (!myWindow.IsActive()||input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}
		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}
		float deltaTime = TimeUtil::GetDeltaTime();

#if defined(_DEBUG)
		if (deltaTime > 0.5f)
		{
			continue;
		}
		mCurrentState->Update(deltaTime);

		GraphicsSystem* gs = GraphicsSystem::Get();
		gs->BeginRender();
		mCurrentState->Render();
		mCurrentState->DebugUI();
		gs->EndRender();
	}
#endif

	LOG("App Is Terminating");
	// 终止最终阶段
	mCurrentState->Terminate();

	// 终止所有单例模式实例
	GraphicsSystem::StaticTerminate();
	InputSystem::StaticTerminate();
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