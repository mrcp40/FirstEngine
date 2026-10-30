#pragma once

#include <FirstEngine/Inc/FirstEngine.h>

class MainState :public FirstEngine::AppState
{
public:
	void Initialize()override;
	void Update(float deltaTime) override;
	void Terminate() override;
};
