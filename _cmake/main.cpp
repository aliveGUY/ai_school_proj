#include <wx/wx.h>

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 200)) {
        wxPanel* panel = new wxPanel(this, wxID_ANY);

        wxStaticText* greeting = new wxStaticText(panel, wxID_ANY, "Hello, wxWidgets!", wxPoint(10, 10));
        greeting->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

        Centre();
    }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MyFrame* frame = new MyFrame("Hello, wxWidgets");
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
