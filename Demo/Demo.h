#pragma once

#include "resource.h"
struct diem
{
	int x; 
	int y;
};
WCHAR *tenfile;						//Dùng để lưu tên file khi mở file hoặc save file

WCHAR* OpenFileSave(HWND hWnd);
void SaveAnh(HWND hwnd, HDC hdc, WCHAR* duongdan);

COLORREF ShowColorDialog(HWND hwnd);
COLORREF mau_ve = RGB(0, 0, 0);
Point bat_Dau, ket_Thuc;
HDC	hdc_ao;
HBITMAP	bitmap_ao;

GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;

WCHAR * ten_file;
BITMAP doi_tuong_ve;
string loai = "";
int so_Luong_phanTu = 0;
int kich_thuoc_but = 1;
bool chuot_trai = false;
bool ve_Tam = true;
bool hcn = false;
HDC hdc;