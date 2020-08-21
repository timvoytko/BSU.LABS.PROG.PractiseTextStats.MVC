#pragma once
#include"Controller.h"
LRESULT Controller::MessageCheck(UINT message, WPARAM wParam, LPARAM lParam) {
    static int cx, cy;
    RECT rt;
    static int row_number;
    switch (message)
    {
    case WM_SIZE:
        cx = LOWORD(lParam);
        cy = HIWORD(lParam);
        GetClientRect(view_.GetListBox(), &rt);
        rt.bottom = 6 * cy / 7;
        rt.right = cx / 4;
        SetWindowPos(view_.GetListBox(), 0, 0, 0, rt.right, rt.bottom, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        view_.SetWindowSize(cx, cy);
        GetClientRect(hEdit_, &rt);
        rt.right = cx / 8;
        rt.bottom = cy / 24;
        SetWindowPos(hEdit_, 0, cx / 100, 6 * cy / 7, cx / 8, cy / 24, SWP_NOZORDER | SWP_NOACTIVATE);
        GetClientRect(hButton_, &rt);
        SetWindowPos(hButton_, 0, cx / 100, 6 * cy / 7 + cy / 24, cx / 12, cy / 20, SWP_NOZORDER | SWP_NOACTIVATE);
        rt.right = cx / 12;
        rt.left = cy / 20;
        SendMessage(view_.GetMainWindow(), WM_COMMAND, MAKELONG(IDC_LISTBOX_TEXT, LBN_SELCHANGE), 0);
        break;
    case WM_CREATE:
        SetWindowTextA(view_.GetMainWindow(), "Text Stats");
        view_.SetListBox(CreateWindowExW(WS_EX_CLIENTEDGE
            , L"LISTBOX", NULL
            , WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_AUTOVSCROLL | LBS_NOTIFY | ES_AUTOHSCROLL
            , 0, 0, 0, 0
            , view_.GetMainWindow(), (HMENU)IDC_LISTBOX_TEXT, hInst_, NULL));
        hButton_ = CreateWindowExW(WS_EX_APPWINDOW
         , L"BUTTON", NULL
         , WS_CHILD | WS_VISIBLE
         , 20,670,100,20
         , view_.GetMainWindow(), (HMENU)IDC_BUTTON, hInst_, NULL);
        hEdit_ = CreateWindowEx(
           WS_EX_CLIENTEDGE, "EDIT",
           NULL,
           WS_CHILD | WS_VISIBLE | ES_LEFT | ES_NUMBER,
           20, 630, 120,30,
            view_.GetMainWindow(),
           (HMENU)IDC_EDIT,
           hInst_,
           NULL);
        SetWindowTextA(hButton_, "CLICK");
        view_.ShowListBox();
        break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON:
            row_number=GetDlgItemInt(view_.GetMainWindow(), IDC_EDIT, NULL, NULL);
            if (row_number <= 0||row_number>model_.GetTextRows().size()) {
                view_.Error();
            }
            else {
                model_.SetStrokeNumber(row_number - 1);
                SendMessage(view_.GetListBox(), LB_SETCURSEL, row_number - 1, 0);
                view_.ShowStats();
            }
            break;
        case IDC_LISTBOX_TEXT:
            switch (HIWORD(wParam))
            {
            case LBN_SELCHANGE:
            {
                row_number = -1;
                row_number = SendMessage(view_.GetListBox(), LB_GETCURSEL, 0, 0);
                if (row_number == -1)break;
                model_.SetStrokeNumber(row_number);
                view_.ShowStats();

            }
            break;
            case IDM_EXIT:
                DestroyWindow(view_.GetMainWindow());
                break;
            default:
                return DefWindowProc(view_.GetMainWindow(), message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(view_.GetMainWindow(), message, wParam, lParam);
    }
    }
}