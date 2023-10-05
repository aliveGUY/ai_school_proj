#include <wx/wx.h>
#include <asio.hpp>
#include "presentation/MainFrame.h"


class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame("Hello, wxWidgets");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
