#include "windows.h"
#include "strsafe.h"
#define IDC_LIST 1
#define IDC_STATIC 2
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hinst;
typedef struct 
{ 
	TCHAR name[30]; 
	TCHAR info[100]; 
}Friends; 
Friends friends[] =  
{ 
	{TEXT("Pham Trung Hieu"), TEXT("Role: Leader\nDate: 01/01/2003\nAddress:ThaiBinh\nWork: 63KTPM2\nID:2151170557")}, 
	{TEXT("Le Van Hoan"), TEXT("Role: Member\nDate: 02/02/2003\nAddress:BacGiang\nWork: 63KTPM2\nID:2151173773")}, 
	{TEXT("Trinh Cong Huy Hoang"), TEXT("Role: Member\nDate: 03/03/2003\nAddress:HaGiang\nWork: 63KTPM2\nID:2151170576")}, 
	{TEXT("Nguyen Trong Hoang"), TEXT("Role: Member\nDate: 04/04/2003\nAddress:HaNoi\nWork: 63KTPM2\nID:2151173774")}, 
	{TEXT("Do Huy Hoang"), TEXT("Role: Member\nDate: 05/05/2003\nAddress:HaiDuong\nWork: 63KTPM2\nID:215117")}, 
}; 
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	MSG msg ; 
	WNDCLASS wc = {0};
	wc.lpszClassName = TEXT( "Application" );
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	g_hinst = hInstance;
	RegisterClass(&wc);
	CreateWindow(wc.lpszClassName, TEXT("List Box"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 400, 200, 0, 0, hInstance, 0); 
	while( GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndList, hwndStatic;
	int i, sel;
	TCHAR buff[100];
	switch(msg) 
	{
		case WM_CREATE:
			hwndList = CreateWindow(TEXT("listbox") , NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY,20, 20, 150, 120, hwnd,(HMENU) IDC_LIST, g_hinst, NULL);
			hwndStatic = CreateWindow(TEXT("static") , NULL, WS_CHILD | WS_VISIBLE,220, 20, 160, 100, hwnd,(HMENU) IDC_STATIC, g_hinst, NULL);
			for (i = 0; i < ARRAYSIZE(friends); i++) 
			{ 
				SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM) friends[i].name); 
			} 
			break;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDC_LIST) 
			{ 
				if (HIWORD(wParam) == LBN_SELCHANGE) 
				{ 
					sel = (int) SendMessage(hwndList, LB_GETCURSEL, 0, 0);
					StringCbPrintf(buff, ARRAYSIZE(buff), TEXT("%s"), friends[sel].info);
					SetWindowText(hwndStatic, buff);
				}
			} 
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hwnd, msg, wParam, lParam));
}
