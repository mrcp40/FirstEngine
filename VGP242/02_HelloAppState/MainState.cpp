#include "MainState.h"

using namespace FirstEngine::Input;
void MainState::Initialize()
{
	LOG("MAIN STATE INITIALIZED");

}

void MainState::Update(float deltaTime)
{
	if (InputSystem::Get()->IsKeyPressed(KeyCode::SPACE))
	{
		FirstEngine::MainApp().ChangeState("GameState");
	}
}

void MainState::Terminate()
{
	LOG("MAIN STATE IS TERMINATE");
}
