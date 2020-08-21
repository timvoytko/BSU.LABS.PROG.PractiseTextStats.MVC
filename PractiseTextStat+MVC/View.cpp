#pragma once
#include"View.h"
void View::SetModel(StatsModel& model) {
    model_ = model;
}
void View::SetWindow(HWND hwnd) {
    hwnd_ = hwnd;
}
void View::SetWindowSize(int cx, int cy) {
    cx_ = cx;
    cy_ = cy;
}
void View::ShowListBox() {
    std::vector<std::string> rows = model_.GetTextRows();
    for (int i = 0; i < rows.size(); i++) {
        const char* tmp = rows[i].c_str();
        SendMessage(hListBox_, LB_ADDSTRING, 0, (LPARAM)(LPCSTR)tmp);
    }
}
void View::Error(){
    MessageBox(hwnd_, "ERROR", 0, MB_OK);
}
void View::ShowStats() {
    static HDC hdc;
    static HBRUSH hbrush;
    std::string tmptext, chartext;
    int tmpy, x1, x2;
    static HFONT font;
    PAINTSTRUCT ps;
    std::vector<std::pair<int, double>> length_stat = model_.GetLengthStat();
    std::vector<std::pair<char, double>> letter_stat = model_.GetLetterStat();
    static RECT rt;
    font = CreateFont(cy_ / (2 * letter_stat.size()), 6, 0, 0, 0, 1, 0, 0,
        DEFAULT_CHARSET, 0, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
    hdc = GetDC(hwnd_);
    SetRect(&rt, cx_ / 4, 0, cx_, cy_);
    FillRect(hdc, &rt, CreateSolidBrush(RGB(255, 255, 255)));
    tmpy = cy_ / 10;
    SelectObject(hdc, font);
    SetTextColor(hdc, RGB(0, 0, 0));
    if (letter_stat.size() == 1) {
        font = CreateFont(cy_ /10, 6, 0, 0, 0, 1, 0, 0,
            DEFAULT_CHARSET, 0, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
        SelectObject(hdc, font);
        hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SetRect(&rt, cx_ / 3, cy_/10, cx_ / 3 + cx_ / 4 ,cy_/10+cy_/10 );
        FillRect(hdc, &rt, hbrush);
        chartext = letter_stat[0].first;
        tmptext = "Symbol: " + chartext + " ";
        TextOut(hdc, cx_ / 3 - cx_ / 12, cy_ / 10, tmptext.c_str(), tmptext.length());
        tmptext = std::to_string(letter_stat[0].second * 100) + "%";
        TextOut(hdc, cx_ / 3 + cx_/4, tmpy, tmptext.c_str(), tmptext.length());
    }
    else {
        for (int i = 0; i < letter_stat.size(); i++) {
            hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
            SetRect(&rt, cx_ / 3, tmpy, cx_ / 3 + cx_ / 4 * letter_stat[i].second, tmpy + cy_ / (2 * letter_stat.size()));
            FillRect(hdc, &rt, hbrush);
            chartext = letter_stat[i].first;
            tmptext = "Symbol: " + chartext + " ";
            TextOut(hdc, cx_ / 3 - cx_ / 12, tmpy, tmptext.c_str(), tmptext.length());
            tmptext = std::to_string(letter_stat[i].second * 100) + "%";
            TextOut(hdc, cx_ / 3 + cx_ / 3 * letter_stat[i].second, tmpy, tmptext.c_str(), tmptext.length());
            tmpy += cy_ / (2 * letter_stat.size());
        }
    }
   
   
    if (length_stat.size() == 1) {
        font = CreateFont(cx_/28, 6, 2700, 0, 0, 1, 0, 0,
            DEFAULT_CHARSET, 0, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
        SelectObject(hdc, font);

        hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
        SetRect(&rt, 2*cx_/3,0, 2 * cx_ / 3+cx_/14, cy_ / 2);
        FillRect(hdc, &rt, hbrush);
        tmptext = "Length: " + std::to_string(length_stat[0].first) + " " + std::to_string(length_stat[0].second * 100) + "%";
        TextOut(hdc, 2*cx_/3+cx_/28, cy_ / 2, tmptext.c_str(), tmptext.length());
    }
    else {
        x1 = 2 * cx_ / 3;
        x2 = x1 + 10 * cx_ / (35 * length_stat.size());
        font = CreateFont((x2 - x1) / 4, 6, 2700, 0, 0, 1, 0, 0,
            DEFAULT_CHARSET, 0, CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, _T("Arial"));
        SelectObject(hdc, font);
        for (int i = 0; i < length_stat.size(); i++) {
            hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
            SetRect(&rt, x1, cy_ / 2 - cy_ * length_stat[i].second / 2, x2, cy_ / 2);
            FillRect(hdc, &rt, hbrush);
            tmptext = "Length: " + std::to_string(length_stat[i].first) + " " + std::to_string(length_stat[i].second * 100) + "%";
            TextOut(hdc, x1 + (x2 - x1) / 2, cy_ / 2, tmptext.c_str(), tmptext.length());
            x1 += 10 * cx_ / (35 * length_stat.size());
            x2 += 10 * cx_ / (35 * length_stat.size());
        }
    }
    EndPaint(hwnd_, &ps);
}
const HWND View::GetMainWindow(){
    return hwnd_;
}
const HWND View::GetListBox(){
    return hListBox_;
}
void View::SetListBox(HWND hListBox){
    hListBox_ = hListBox;
}
const std::pair<int, int> View::GetWindowSize(){
    return {cx_,cy_};
}
const StatsModel View::GetModel(){
    return model_;
}