// Demo.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Demo.h"
#include <objbase.h>
#pragma comment(lib,"Ole32.lib")
#include "RibbonFramework.h"
#include "RibbonIDs.h"
#include <shellapi.h>
#pragma commment (lib,"shell32.lib")
#define MAX_LOADSTRING 100
HINSTANCE hInst;    


WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Khai báo

void tinh_toan_hv_elip(Point &, Point &);


class hinh
{
public:
	Point diem_bat_dau;
	Point diem_ket_thuc;
	Pen *but = new Pen (Color(255,255,255,0));
	SolidBrush *mau_to = new SolidBrush(Color(255,0,255,0));
	virtual void ve(Graphics * grap) = 0;
	//virtual hinh* khoi_tao(diem bat_dau, diem ket_thuc) = 0;
	void set_viti(Point x, Point y)
	{
		diem_bat_dau = x;
		diem_ket_thuc = y;
	}
	void set_but(Pen *pen, SolidBrush *mau)
	{
		but = pen;
		mau_to = mau;
	}
	hinh() {};
};

class duong_thang :public hinh
{
public:
	
	void ve(Graphics * grap)
	{
		grap->DrawLine(but, diem_bat_dau, diem_ket_thuc);
	}
	
	duong_thang() {};

};
class hinh_chu_nhat :public hinh
{
public:
	
	void ve(Graphics * grap)
	{
		grap->DrawRectangle(but,diem_bat_dau.X,diem_bat_dau.Y,
					diem_ket_thuc.X -diem_bat_dau.X,diem_ket_thuc.Y-diem_bat_dau.Y);
		
	}
	
	hinh_chu_nhat() {};
};
class hinh_vuong :public hinh
{
public:
	
	void ve(Graphics *grap)
	{
			tinh_toan_hv_elip(diem_bat_dau, diem_ket_thuc);
			grap->DrawRectangle(but, diem_bat_dau.X, diem_bat_dau.Y,
				diem_ket_thuc.X - diem_bat_dau.X, diem_ket_thuc.Y - diem_bat_dau.Y);
	}
};

class hinh_elip : public hinh
{
public:
	
	void ve(Graphics *grap)
	{
		grap->DrawEllipse(but, diem_bat_dau.X, diem_bat_dau.Y,
			diem_ket_thuc.X - diem_bat_dau.X, diem_ket_thuc.Y - diem_bat_dau.Y);
	}

	hinh_elip() {};
};

class hinh_tron : public hinh
{
public:
	
	void ve(Graphics *grap)
	{
		tinh_toan_hv_elip(diem_bat_dau, diem_ket_thuc);
			grap->DrawEllipse(but, diem_bat_dau.X, diem_bat_dau.Y,
				diem_ket_thuc.X - diem_bat_dau.X, diem_ket_thuc.Y - diem_bat_dau.Y);
	}

	hinh_tron() {};
};
vector <hinh*> mang_vi_tri;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	ShellExecute(0, 0, L"Ribbon.bat", 0, 0, 0);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // TODO: Place code here.
	CoInitialize(NULL);
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMO));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	CoUninitialize();
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
hinh* temp = NULL;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
	case WM_CREATE:
		InitializeFramework(hWnd);
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		break;
	case WM_MOUSEMOVE:
	{
		if (chuot_trai)
		{
			Point tam;
			tam.X = GET_X_LPARAM(lParam);
			tam.Y = GET_Y_LPARAM(lParam);


			WCHAR buf[1000];
			wsprintf(buf, L"%d  %d", tam.X,tam.Y);
			SetWindowText(hWnd, buf);

			if (ve_Tam )
			{
				ket_Thuc = tam;
				temp->set_viti(bat_Dau, ket_Thuc);
				InvalidateRect(hWnd, 0, FALSE); //Goi ham WM_PAINT
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		
		bat_Dau.X = GET_X_LPARAM(lParam);
		bat_Dau.Y = GET_Y_LPARAM(lParam);
		chuot_trai = true;
		if (loai == "") temp = new duong_thang;
		if (loai == "hv") temp = new hinh_vuong;
		else
		{
			if (loai == "hcn") temp = new hinh_chu_nhat;
			if (loai == "dt") temp = new duong_thang;
			if (loai == "he") temp = new hinh_elip;
			if (loai == "ht") temp = new hinh_tron;
		}
		SetCapture(hWnd);
		break;
	}
	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		chuot_trai = false;
		if (temp != NULL) 
			mang_vi_tri.push_back(temp);
		break;
	}
	
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);		
      
			case ID_open:
			{
				MessageBox(hWnd, L"Chưa có tính năng này", L"Thông báo", MB_OK);
				break;
			}
			case ID_save: //save file
			{
				tenfile = OpenFileSave(hWnd);
				SaveAnh(hWnd, GetDC(hWnd), tenfile);
				break;
			}
			case ID_Duong_thang: //duong thang
			{
				loai = "dt";
				break;
			}
				
			case ID_Hinh_chu_nhat: // hình chữ nhật
			{	
				loai = "hcn";
				break;
			}
			case ID_Hinh_vuong: //hình vuông
			{
				loai = "hv";
				break;
			}
				
			case ID_Hinh_elip: // hình elip
			{
				loai = "he";
				break;
			}
			case ID_Hinh_tron: //hinh tròn
			{
				loai = "ht";
				break;
			}
            case ID_exit:
                DestroyWindow(hWnd);
                break;
			case ID_EDIT_C:
				mau_ve = ShowColorDialog(hWnd);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);
			hdc_ao = CreateCompatibleDC(hdc); // tao 1 hdc_ao
			
			
			bitmap_ao = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);	//tạo 1 bitmap ảo
			SelectObject(hdc_ao, bitmap_ao);
			FillRect(hdc_ao, &rect, (HBRUSH)(COLOR_WINDOW + 1));   //tô màu cho hdc ảo
			

			//dung GDI+
			Graphics*graphics = new Graphics(hdc_ao);
			Pen* pen = new Pen(Color(255,0,0,0),2);
			SolidBrush * mau = new SolidBrush(Color(255, 0, 255, 0));

			for (int i = 0; i < mang_vi_tri.size(); i++)
			{
				mang_vi_tri[i]->ve(graphics);
			}

			if (ve_Tam && chuot_trai) 
			{
				temp->set_but(pen, mau);
				temp->ve(graphics);
			}
			BitBlt(hdc, 0, 0, rect.right, rect.bottom,hdc_ao, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		//DestroyFramework();
		GdiplusShutdown(gdiplusToken);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

COLORREF ShowColorDialog(HWND hwnd)
{
	CHOOSECOLOR cc;
	static COLORREF crCustClr[16];
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)crCustClr;
	cc.rgbResult = RGB(0, 255, 0);		// nếu không chọn bảng thì trả về mặt định là màu xanh lá
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	ChooseColor(&cc);
	return cc.rgbResult;
}

TCHAR szFile[260];// Biến toàn cực  để cấp địa chỉ
WCHAR* OpenFileSave(HWND hWnd)
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	wcscpy(szFile, L"tentam.bmp");
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"File bitmap (*.bmp)\0*.BMP\0All Files (*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	GetSaveFileName(&ofn);
	return ofn.lpstrFile;
}
void SaveAnh(HWND hwnd, HDC hdc, WCHAR* duongdan)
{
	HDC hdc_tam = CreateCompatibleDC(hdc);


	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
	HBITMAP hbmScreen = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);
	SelectObject(hdc_tam, hbmScreen);
	int chieucaoribbon = 145;
	BitBlt(hdc_tam, 0, chieucaoribbon, rcClient.right, rcClient.bottom, hdc,0, chieucaoribbon,  SRCCOPY);
	BITMAP bmpScreen;

	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
	// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
	// have greater overhead than HeapAlloc.
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap and copies them into a buffer 
	// which is pointed to by lpbitmap.
	GetDIBits(hdc, hbmScreen, 0, (UINT)bmpScreen.bmHeight, lpbitmap, (BITMAPINFO *)&bi, DIB_RGB_COLORS);

	// A file is created, this is where we will save the screen capture.
	HANDLE hFile = CreateFile(duongdan,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;
	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

}



void tinh_toan_hv_elip(Point &diem_bat_dau,Point &diem_ket_thuc)
{
	int bd = abs(diem_bat_dau.X - diem_ket_thuc.X); //do dai canh trục x
	int kt = abs(diem_bat_dau.Y - diem_ket_thuc.Y); //do dai canh truc y
	if (bd < kt)
	{
		if (diem_bat_dau.Y < diem_ket_thuc.Y)
			diem_ket_thuc.Y = diem_bat_dau.Y + bd;
		else diem_ket_thuc.Y = diem_bat_dau.Y - bd;
	}
	else
	{
		if (diem_bat_dau.X < diem_ket_thuc.X)
			diem_ket_thuc.X = diem_bat_dau.X + kt;
		else diem_ket_thuc.X = diem_bat_dau.X - kt;
	}
}