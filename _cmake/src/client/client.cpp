#include <wx/wx.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "presentation/MainFrame.h"

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    srand(static_cast<unsigned int>(time(NULL)));
    wxInitAllImageHandlers();
    MainFrame *frame = new MainFrame("Dashboard Example", wxPoint(50, 50), wxSize(800, 600));
    frame->Show(true);
    return true;
}

wxIMPLEMENT_APP(MyApp);
