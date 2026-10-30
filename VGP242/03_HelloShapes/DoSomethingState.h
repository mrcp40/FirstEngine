#pragma once

#include <FirstEngine/Inc/FirstEngine.h>

class DoSomethingState :public FirstEngine::AppState
{
public:
	void Initialize()override;
	void Update(float deltaTime) override;
	void Render() override;
	void Terminate() override;
private:
	struct Vertex
	{
		FirstEngine::Math::Vector3 position = FirstEngine::Math::Vector3::Zero;
	};
	using Vertices = std::vector<Vertex>;
	Vertices mVertecies;
	ID3D11Buffer* mVertexBuffer = nullptr; // shape information

	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};