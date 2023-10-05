#pragma once

#include <wx/wx.h>
#include "State.h"
#include "Dashboard.h"

class NavigationPanel : public wxPanel
{
public:
    NavigationPanel(wxWindow *parent, State &state, Dashboard *dashboard);

private:
    State &state;
    Dashboard *dashboard;
    wxButton *button1;
    wxButton *button2;

    void OnOption1Click(wxCommandEvent &event);
    void OnOption2Click(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};
