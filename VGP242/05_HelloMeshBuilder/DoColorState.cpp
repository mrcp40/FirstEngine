#include "DoColorState.h"

using namespace FirstEngine;
using namespace FirstEngine::Graphics;
using namespace FirstEngine::Input;

void DoColorState::Initialize()
{
	// setup camera
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	// create a shape 
	//MeshPC cube = MeshBuilder::CreateCubePC(1.0f);
	//MeshPC cube = MeshBuilder::CreateRectanglePC(2.0f,10.0f,4.0f);
	//MeshPC plane = MeshBuilder::CreatePlanePC(10, 10, 1.0f);
	//MeshPC mesh = MeshBuilder::CreateCylinderPC(30, 3);
	//MeshPC mesh = MeshBuilder::CreateSpherePC(30, 30, 1.0f);
	MeshPC mesh = MeshBuilder::CreatePyramid(1.0f);


	mMeshBuffer.Initialize(mesh);
	std::filesystem::path shaderPath = L"../../Assets/Shaders/DoTransform.fx";

	mVertexShader.Initialize<VertexPC>(shaderPath);
	mPixelShader.Initialize(shaderPath);
	mTransformBuffer.Initialize(sizeof(Math::Matrix4));
}
void DoColorState::Update(float deltaTime)
{
	InputSystem* input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT)) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;
	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}
void DoColorState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mTransformBuffer.BindVS(0);

	Math::Matrix4 matWorld = Math::Matrix4::Identity;
	Math::Matrix4 matView = mCamera.GetViewMatrix();
	Math::Matrix4 matProj = mCamera.GetProjectionMatrix();
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Math::Transpose(matFinal);
	mTransformBuffer.Update(&wvp);

	mMeshBuffer.Render();


}
void DoColorState::Terminate()
{
	mVertexShader.Terminate();
	mPixelShader.Terminate();
	mMeshBuffer.Terminate();
	mTransformBuffer.Terminate();
}