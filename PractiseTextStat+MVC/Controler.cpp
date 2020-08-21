#pragma once
#include"Controler.h"
void Controler::CreateControlers(HWND* hwnd) {
    SetWindowText(*hwnd, "Text Stats");
    hButton_ = CreateWindowExW(WS_EX_APPWINDOW
        , L"BUTTON", NULL
        , WS_CHILD | WS_VISIBLE
        , 0, 0, 0, 0
        , *hwnd, (HMENU)IDC_BUTTON, *hInst_, NULL);
    hEdit_ = CreateWindowEx(
        WS_EX_CLIENTEDGE, "EDIT",
        NULL,
        WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
        0, 0, 0, 0,
        *hwnd,
        (HMENU)IDC_EDIT,
        *hInst_,

        NULL);
    SetWindowTextA(hButton_, "CLICK");
}
void Controler::UpdateControlSize(int cx, int cy) {
    RECT rt;
    GetClientRect(hEdit_, &rt);
    rt.right = cx / 8;
    rt.bottom = cy / 24;
    SetWindowPos(hEdit_, 0, cx / 100, 6 * cy / 7, cx / 8, cy / 24, SWP_NOZORDER | SWP_NOACTIVATE);
    GetClientRect(hButton_, &rt);
    SetWindowPos(hButton_, 0, cx / 100, 6 * cy / 7 + cy / 24, cx / 12, cy / 20, SWP_NOZORDER | SWP_NOACTIVATE);
    rt.right = cx / 12;
    rt.left = cy / 20;
}
