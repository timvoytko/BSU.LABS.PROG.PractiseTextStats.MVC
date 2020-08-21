#pragma once

#include"View.h"

class Controler  {
protected:
    StatsModel* model_;
    HINSTANCE *hInst_;
    HWND hButton_, hEdit_;
public:
    Controler() = default;
    Controler(StatsModel* model,  HINSTANCE*hInst) : model_(model),   hInst_(hInst) {}
    void UpdateControlSize(int cx, int cy);
    void CreateControlers(HWND*);
};
