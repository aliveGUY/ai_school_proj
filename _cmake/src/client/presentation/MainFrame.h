#pragma once

#include <wx/wx.h>
#include "State.h"
#include "Dashboard.h"
#include "NavigationPanel.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
    State state;

private:
    wxBoxSizer *mainSizer;
    Dashboard *dashboard;
    NavigationPanel *navigationPanel;
};
