#include "ContentPanel.h"

wxBEGIN_EVENT_TABLE(ContentPanel, wxPanel)
    EVT_LEFT_DOWN(ContentPanel::OnContentClick)
wxEND_EVENT_TABLE()

ContentPanel::ContentPanel(wxWindow *parent, const wxString &title, const wxColour &color)
    : wxPanel(parent), title(title), color(color)
{
    // Set the background color of the panel
    SetBackgroundColour(color);

    // Set the desired width and height
    int width = 180;  // Adjust as needed
    int height = 200; // Adjust as needed

    // Set the size of the content panel
    SetMinSize(wxSize(width, height));
    SetMaxSize(wxSize(width, height));

    // Create a label to display the content's title
    wxStaticText *titleCtrl = new wxStaticText(this, wxID_ANY, title);
    titleCtrl->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // Create a sizer for the content panel
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(titleCtrl, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP, 10);

    SetSizer(sizer);
}

void ContentPanel::OnContentClick(wxMouseEvent &event)
{
    // Handle the click event here, e.g., open the content or perform an action
    wxMessageBox("Clicked on: " + title, "Content Clicked");
    event.Skip(); // Allow further processing of the event
}
