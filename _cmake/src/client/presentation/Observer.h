#pragma once

#include <wx/wx.h>

class Observer
{
public:
    virtual void update(wxColour &color) = 0;
};
