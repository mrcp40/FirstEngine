#pragma once

#include <Core/Inc/Core.h>
#include <Math/Inc/EngineMath.h>

// directX
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXTK/Inc/CommonStates.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

template<class T>
inline void SafeRelease(T*& ptr)
{
	if (ptr != nullptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}
