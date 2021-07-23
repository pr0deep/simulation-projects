#include "Graphics.h"

Graphics::Graphics() {
	factory = NULL;
	renderTarget = NULL;
	writeFactory = NULL;
}

Graphics::~Graphics() {
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();
}

void Graphics::init(HWND windowHandle) {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (res != S_OK) return;

	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(writeFactory),reinterpret_cast<IUnknown **>(&writeFactory));
	if (res != S_OK) return;
	writeFactory->CreateTextFormat(
		L"Verdana",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20,
		L"",
		&textFormat
	);


	RECT rect;
	GetClientRect(windowHandle, &rect);

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)), &renderTarget
	);
	if (res != S_OK) return;

	renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &darkBrush);
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1), &lightBrush);

}

void Graphics::ClearScreen(float r, float g, float b) {
	renderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b) {
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &brush);
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2(x, y), radius, radius);

	renderTarget->DrawEllipse(ellipse, brush, 3.0f);
	renderTarget->FillEllipse(ellipse, brush);

	brush->Release();
}

void Graphics::DrawLine(float x1,float y1,float x2,float y2,float r,float g,float b) {
	ID2D1SolidColorBrush* brush;
	renderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &brush);
	auto p1 = D2D1::Point2(x1, y1);
	auto p2 = D2D1::Point2(x2, y2);

	renderTarget->DrawLine(p1, p2, brush,2);

	brush->Release();
}

void Graphics::CustomDrawText(float x,float y,const WCHAR* string,int length){
	auto size = renderTarget->GetSize();
	renderTarget->DrawTextW(string,length,textFormat,D2D1::RectF(x,y,size.width,size.height),lightBrush);
}