#include "GameState.h"


using namespace FirstEngine::Input;
void GameState::Initialize()
{
	LOG("GAME STATE INITIALIZED");

}

void GameState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		FirstEngine::MainApp().ChangeState("MainState");
	}
}

void GameState::Terminate()
{
	LOG("GAME STATE IS TERMINATE");
}