#pragma once
#include"View.h"
class Controller  {
private:
    StatsModel& model_;
    View& view_;
    HINSTANCE hInst_;
    HWND hButton_, hEdit_;
public:
    Controller(StatsModel& model, View& view, HINSTANCE hInst) : model_(model), view_(view),  hInst_(hInst) {}
    LRESULT MessageCheck(UINT message, WPARAM wParam, LPARAM lParam);
};
