#include <windows.h>
#include "main.h"
#include "Graphics.h"
#include "Pendulum.h"

//make a graphics object..
Graphics* graphicsContext;

//make a pendulum object to manage the pendulum...
Pendulum* pendulum;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    HWND SimHWND = CreateHWND(hInstance,L"Pendulum Class Window",L"Title");
    if (!SimHWND) return 0;

    //create a new context obj for the current handler..
    graphicsContext = new Graphics();
    graphicsContext->init(SimHWND);
    //end

    //Initialising pendulum properties
    RECT clientRect;
    GetClientRect(SimHWND, &clientRect);

    float pendulum_x = (clientRect.left + clientRect.right)/2, pendulum_y = 100, pendulum_r = 30, pendulum_l = 300;
    pendulum = new Pendulum(pendulum_x,pendulum_y,pendulum_l,pendulum_r);
    //end


    ShowWindow(SimHWND, nCmdShow);
    
    // Main Loop ...
    int i = 0;
    MSG msg;
    msg.message = NULL;
    while (msg.message != WM_QUIT) {
    
        if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    
        else {
        //update physics...
            pendulum->update();
        //render methods...
            //making a clean canvas...
            graphicsContext->BeginDraw();
            graphicsContext->ClearScreen(0, 0, 0);
            
            //render...
            pendulum->draw(graphicsContext);
            //end
            graphicsContext->EndDraw();
        }
    }

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


HWND CreateHWND(HINSTANCE hInstance,const wchar_t *className,const wchar_t *Title) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"new main window class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Pendulum Simulator",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );
    return hwnd;
}