#pragma once

#include <wx/wx.h>
#include <vector>
#include "Observer.h"

class Subject
{
public:
    virtual void registerObserver(Observer *observer) = 0;
    virtual void removeObserver(Observer *observer) = 0;
    virtual void notifyObservers() = 0;
};

class State : public Subject
{
private:
    std::vector<Observer *> observers;
    wxColour color;

public:
    void setState(const wxColour &newColor);
    wxColour getState() const;
    void registerObserver(Observer *observer) override;
    void removeObserver(Observer *observer) override;
    void notifyObservers() override;
};
