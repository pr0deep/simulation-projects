#pragma once

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>

class Graphics {
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	IDWriteFactory* writeFactory;
	IDWriteTextFormat* textFormat;

	ID2D1SolidColorBrush* darkBrush;
	ID2D1SolidColorBrush* lightBrush;

public:
	Graphics();

	~Graphics();

	void init(HWND windowHandle);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b);
	void DrawLine(float x1,float y1,float x2,float y2, float r, float g, float b);
	void CustomDrawText(float x1, float y1,const WCHAR* string,int length);
};