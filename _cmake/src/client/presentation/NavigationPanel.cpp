#include "NavigationPanel.h"

wxBEGIN_EVENT_TABLE(NavigationPanel, wxPanel)
    EVT_BUTTON(wxID_ANY, NavigationPanel::OnOption1Click)
    EVT_BUTTON(wxID_ANY, NavigationPanel::OnOption2Click)
wxEND_EVENT_TABLE()

NavigationPanel::NavigationPanel(wxWindow *parent, State &state, Dashboard *dashboard)
    : wxPanel(parent), state(state), dashboard(dashboard)
{
    // Create buttons for changing colors
    button1 = new wxButton(this, wxID_ANY, "Change Color 1");
    button2 = new wxButton(this, wxID_ANY, "Change Color 2");

    // Create a sizer for the navigation panel
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(button1, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);
    sizer->Add(button2, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);

    SetSizer(sizer);
}

void NavigationPanel::OnOption1Click(wxCommandEvent &event)
{
    state.setState(wxColour(rand() % 256, rand() % 256, rand() % 256));
}

void NavigationPanel::OnOption2Click(wxCommandEvent &event)
{
    state.setState(wxColour(rand() % 256, rand() % 256, rand() % 256));
}
