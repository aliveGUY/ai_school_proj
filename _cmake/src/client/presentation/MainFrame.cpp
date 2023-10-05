#include "MainFrame.h"

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size), state()
{
    mainSizer = new wxBoxSizer(wxVERTICAL);

    navigationPanel = new NavigationPanel(this, state, dashboard);
    mainSizer->Add(navigationPanel, 0, wxEXPAND);
    
    dashboard = new Dashboard(this, state);
    mainSizer->Add(dashboard, 1, wxEXPAND);

    SetSizerAndFit(mainSizer);
    Centre();
}
