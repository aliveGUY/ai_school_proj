#ifndef DASHBOARD_H
#define DASHBOARD_H

// Include necessary headers
#include "ContentPanel.h"
#include <wx/wx.h>
#include "State.h"

class Dashboard : public wxScrolledWindow, public Observer
{
public:
    Dashboard(wxWindow *parent, State &state);
    void update(wxColour &color);
    void display();

private:
    State &glob_state;
    wxFlexGridSizer *contentSizer;
    std::vector<ContentPanel *> contentItems;
};

#endif // DASHBOARD_H
