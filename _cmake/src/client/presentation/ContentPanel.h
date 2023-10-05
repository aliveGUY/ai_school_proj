#pragma once

#include <wx/wx.h>

class ContentPanel : public wxPanel
{
public:
    ContentPanel(wxWindow *parent, const wxString &title, const wxColour &color);
    
private:
    wxString title;
    wxColour color;

    void OnContentClick(wxMouseEvent &event);

    wxDECLARE_EVENT_TABLE();
};
