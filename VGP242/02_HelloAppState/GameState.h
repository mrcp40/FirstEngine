#pragma once

#include <FirstEngine/Inc/FirstEngine.h>

class GameState: public FirstEngine::AppState
{
public:
	void Initialize()override;
	void Update(float deltaTime) override;
	void Terminate() override;

private:

};