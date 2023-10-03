#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

private:
    void OnButtonClicked(wxCommandEvent &evt);
    void OnSliderChange(wxCommandEvent &evt);
    void OnTextChanged(wxCommandEvent &evt);
};