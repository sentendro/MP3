#include "GWindow.h"
bool keyDown[256];
int mouseX, mouseY;
bool mouseButtonDown[3];
bool IsKeyDown(BYTE key){
	return keyDown[key];
}

int GetMouseX(){
	return mouseX;
}

int GetMouseY(){
	return mouseY;
}

bool IsMouseDown(int mouseButton){
	return mouseButtonDown[mouseButton];
}

LRESULT CALLBACK GWindow::WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	HWND hWndButton;
	switch (iMsg){
	case WM_KEYDOWN:
		keyDown[wParam] = true;
		break;
	case WM_KEYUP:
		keyDown[wParam] = false;
		break;
	case WM_LBUTTONDOWN:
		mouseButtonDown[0] = true;
		break;
	case WM_RBUTTONDOWN:
		mouseButtonDown[1] = true;
		break;
	case WM_LBUTTONUP:
		mouseButtonDown[0] = false;
		break;
	case WM_RBUTTONUP:
		mouseButtonDown[1] = false;
		break;
	case WM_MOUSEMOVE:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;
}

GWindow::GWindow(GScene * scene)
{
	WNDCLASS WndClass = {
		0, WndProc, 0, 0, GetModuleHandle( NULL ) , 0, 0, 0, 0, L"MyWindow"
	};/*
	WNDCLASSEX WndClass;
	WndClass.hInstance = g_hInst;
	WndClass.lpszClassName = TEXT("TEST");
	WndClass.lpfnWndProc = WndProc;
	WndClass.style = CS_DBLCLKS;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.lpszMenuName = NULL;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	*/
	RegisterClass(&WndClass);

	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;

	hWnd = CreateWindowEx(0,L"MyWindow", L"Window", WS_OVERLAPPEDWINDOW, x, y, width, height, 0, 0, WndClass.hInstance, 0);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	this->scene = scene;
}


GWindow::~GWindow()
{

}
void GWindow::messagePump(){
	scene->OnInitialize();								//scene �ʱ�ȭ

	MSG msg;

	while (1){
		if (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE)){
			if (!GetMessage(&msg, 0, 0, 0))
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			scene->OnUpdate();							//scene ����
			scene->OnDraw();							//scene ���
			Sleep(1);
		}
	}

	scene->OnDestroy();									//scene ��ü ����
}

HWND GWindow::getWindowHandle(){
	return hWnd;
}