#include "State.h"

void State::setState(const wxColour &newColor)
{
    color = newColor;
    notifyObservers();
}

wxColour State::getState() const
{
    return color;
}

void State::registerObserver(Observer *observer)
{
    observers.push_back(observer);
}

void State::removeObserver(Observer *observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
        observers.erase(it);
    }
}

void State::notifyObservers()
{
    for (Observer *observer : observers)
    {
        observer->update(color);
    }
}
