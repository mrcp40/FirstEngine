#pragma once

#include <FirstEngine/Inc/FirstEngine.h>

class DoColorState :public FirstEngine::AppState
{
public:
	void Initialize()override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;
private:
	using Vertices = std::vector<FirstEngine::Graphics::VertexPC>;
	Vertices mVertecies;

	FirstEngine::Graphics::MeshBuffer mMeshBuffer;
	FirstEngine::Graphics::VertexShader mVertexShader;
	FirstEngine::Graphics::PixelShader mPixelShader;
	FirstEngine::Graphics::Camera mCamera;
	FirstEngine::Graphics::ConstantBuffer mTransformBuffer;
};