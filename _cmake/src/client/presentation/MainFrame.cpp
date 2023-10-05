#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <iostream>
#include <asio.hpp>

using namespace asio;
using ip::tcp;
using std::cout;
using std::endl;
using std::string;

MainFrame::MainFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 800))
{
    const auto margin = FromDIP(10);

    auto mainSizer = new wxBoxSizer(wxVERTICAL);
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    this->SetBackgroundColour(panel->GetBackgroundColour());

    auto sizer = new wxGridBagSizer(margin, margin);

    std::vector<std::pair<wxGBPosition, wxGBSpan>> items = {
        {{0, 0}, {1, 10}},
        {{1, 0}, {5, 2}},
        {{1, 2}, {5, 8}}};

    auto initialSize = sizer->GetEmptyCellSize() * 2;
    auto topPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, initialSize);
    topPanel->SetBackgroundColour(wxColour(85, 122, 70));
    sizer->Add(topPanel, items[0].first, items[0].second, wxEXPAND);

    auto sidePanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, initialSize);
    sidePanel->SetBackgroundColour(wxColour(122, 157, 84));
    sizer->Add(sidePanel, items[1].first, items[1].second, wxEXPAND);

    auto dashboard = new wxPanel(panel, wxID_ANY, wxDefaultPosition, initialSize);
    wxString textContent = "loading";
    dashboard->SetBackgroundColour(wxColour(242, 238, 157));
    wxStaticText *staticText = new wxStaticText(dashboard, wxID_ANY, textContent, wxPoint(10, 10));
    sizer->Add(dashboard, items[2].first, items[2].second, wxEXPAND);

    sizer->AddGrowableRow(0, 1);
    sizer->AddGrowableRow(3, 6);

    sizer->AddGrowableCol(0, 2);
    sizer->AddGrowableCol(3, 4);

    sizer->SetMinSize(FromDIP(wxSize(400, 400)));

    panel->SetSizer(sizer);

    mainSizer->Add(panel, 1, wxEXPAND | wxALL, margin);
    this->SetSizerAndFit(mainSizer);

    asio::io_service io_service;
    // socket creation
    tcp::socket socket(io_service);
    // connection
    socket.connect(tcp::endpoint(asio::ip::address::from_string("188.163.82.111"), 1234));
    // request/message from client
    const string msg = "Hello from Client!\n";
    asio::error_code error;
    asio::write(socket, asio::buffer(msg), error);
    if (!error)
    {
        textContent += "\nClient sent hello message!";
    }
    else
    {
        textContent += "\nsend failed: " + error.message();
    }
    // getting response from server
    asio::streambuf receive_buffer;
    asio::read(socket, receive_buffer, asio::transfer_all(), error);
    if (error && error != asio::error::eof)
    {
        textContent += "receive failed: " + error.message();
    }
    else
    {
        const char *data = asio::buffer_cast<const char *>(receive_buffer.data());
        staticText->SetLabel(data);
    }
}
