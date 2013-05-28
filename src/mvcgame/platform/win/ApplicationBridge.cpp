
#include <mvcgame/platform/win/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <cassert>

#include <windows.h>

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

namespace mvcgame {

    ApplicationBridge::ApplicationBridge() :
	_app(nullptr), _instance(NULL), _cmdShow(0), _cmdQuit(0)
    {
    }

    IRenderBridge& ApplicationBridge::geRenderBridge()
    {
        return _renderBridge;
    }

    IFilesystemBridge& ApplicationBridge::getFilesystemBridge()
    {
        return _fsBridge;
    }

    void ApplicationBridge::exit()
    {
    }

    void ApplicationBridge::setApplication(Application& app)
    {
        _app = &app;
    }

    void ApplicationBridge::showError(const std::string& error)
    {   
    }

	void ApplicationBridge::setInstance(HINSTANCE instance)
	{
		_instance = instance;
	}

	void ApplicationBridge::setCmdShow(int cmdShow)
	{
		_cmdShow = cmdShow;
	}

	int ApplicationBridge::getCmdQuit() const
	{
		return _cmdQuit;
	}

    void ApplicationBridge::run()
    {
        assert(_app);
		assert(_instance && _cmdShow);

		HWND hWnd;
		WNDCLASSEX wc;

		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = _instance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = L"WindowClass1";

		RegisterClassEx(&wc);
		hWnd = CreateWindowEx(NULL,
			L"WindowClass1",		// name of the window class
			L"mvcgame",				// title of the window
			WS_OVERLAPPEDWINDOW,	// window style
			300,					// x-position of the window
			300,					// y-position of the window
			500,					// width of the window
			400,					// height of the window
			NULL,					// we have no parent window, NULL
			NULL,					// we aren't using menus, NULL
			_instance,				// application handle
			NULL);					// used with multiple windows, NULL

		ShowWindow(hWnd, _cmdShow);

		MSG msg;

		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_cmdQuit = msg.wParam;
	}
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}