#include "Precompiled.h"
#include "WindowMessageHandler.h"
#include "DebugUtil.h"

using namespace FirstEngine;
using namespace FirstEngine::Core;

void WindowMessagerHandler::Hook(HWND window, Callback cb)
{
	mWindow = window;
	mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void WindowMessagerHandler::Unhook()
{
	SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
	mWindow = nullptr;
}

LRESULT WindowMessagerHandler::ForwardMessage(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ASSERT(mPreviousCallback != nullptr, "WindowMessagerHandler: no callback is hooked!");
	return CallWindowProcA((WNDPROC)mPreviousCallback, window, msg, wParam, lParam);
}