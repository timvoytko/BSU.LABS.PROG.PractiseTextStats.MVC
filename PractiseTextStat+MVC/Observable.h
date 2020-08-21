#pragma once
#include"Observer.h"
#include<vector>
class Observable
{
public:
    void AddObserver(Observer* observer)
    {
        _observers.push_back(observer);
    }
    void NotifyUpdate()
    {
        for (int i = 0; i < _observers.size(); i++)
        {
            _observers[i]->Update();
        }
    }
private:
    std::vector<Observer*> _observers;
};