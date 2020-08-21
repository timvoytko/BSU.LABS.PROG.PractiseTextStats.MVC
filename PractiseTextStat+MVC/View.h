#pragma once
#include"StatsModel.h"
#include"framework.h"
#include"Resource.h"
class View  {
private:
    StatsModel& model_;
    HWND hwnd_, hListBox_;
    int cx_, cy_;
public:
    View(StatsModel& model, HWND hwnd) :model_(model), hwnd_(hwnd) {}
    void SetModel(StatsModel& model);
    void SetWindow(HWND hwnd);
    void SetListBox(HWND hListBox);
    void SetWindowSize(int cx, int cy);
    const HWND GetMainWindow();
    const HWND GetListBox();
    const std::pair<int, int>GetWindowSize();
    const StatsModel GetModel();
    void ShowListBox();
    void ShowStats();
    void Error();
};
