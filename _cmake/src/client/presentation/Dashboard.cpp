#include "Dashboard.h"
#include <wx/wx.h>

Dashboard::Dashboard(wxWindow *parent, State &state)
    : wxScrolledWindow(parent, wxID_ANY), glob_state(state)
{
    glob_state.registerObserver(this);
    display();
}

void Dashboard::update(wxColour &color)
{
    // Update the content panels' background color
    for (ContentPanel *item : contentItems)
    {
        item->SetBackgroundColour(color);
    }

    // Refresh the dashboard to reflect the changes
    Refresh();
}

void Dashboard::display()
{
    this->SetBackgroundColour(wxColour(242, 238, 157));

    contentSizer = new wxFlexGridSizer(4, 10, 10); // 4 columns with a 10-pixel gap
    contentSizer->SetHGap(10);                     // Set horizontal gap between items

    // Create sample content items (25 colored panels)
    for (int i = 1; i <= 25; ++i)
    {
        wxString title = "Content " + wxString::Format("%d", i);
        wxColour color = i % 2 == 0 ? wxColour(100, 100, 255) : wxColour(255, 100, 100);
        ContentPanel *contentItem = new ContentPanel(this, title, color);
        contentItems.push_back(contentItem);
    }

    // Add content items to the content sizer
    for (ContentPanel *item : contentItems)
    {
        // Center-align the content items both horizontally and vertically
        contentSizer->Add(item, 0);
    }

    this->SetSizer(contentSizer);
    this->SetScrollRate(0, 20); // Enable vertical scrolling
}
