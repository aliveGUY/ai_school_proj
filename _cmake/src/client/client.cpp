#include <iostream>
#include <wx/wx.h>
#include <thread>
#include <stdexcept>
#include <chrono>
#include "../bridge/laba_net.h"

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class CustomClient : public laba::net::client_interface<CustomMsgTypes>
{
public:
    void PingServer()
    {
        laba::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    void MessageAll()
    {
        laba::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }
};

std::atomic<bool> bQuit = false;

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnIncreaseState(wxCommandEvent &event);
    void OnMessageAll(wxCommandEvent &event);
    void BackgroundThread();

    wxButton *increaseButton;
    wxButton *messageAllButton;

    CustomClient c;
    std::thread backgroundThread;
};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    increaseButton = new wxButton(this, wxID_ANY, "Ping server", wxPoint(20, 20));
    messageAllButton = new wxButton(this, wxID_ANY, "messageAll", wxPoint(20, 60));

    Connect(increaseButton->GetId(), wxEVT_BUTTON, wxCommandEventHandler(MyFrame::OnIncreaseState));
    Connect(messageAllButton->GetId(), wxEVT_BUTTON, wxCommandEventHandler(MyFrame::OnMessageAll));

    c.Connect("127.0.0.1", 60000);

    // Start the background thread
    backgroundThread = std::thread(&MyFrame::BackgroundThread, this);

    // Initialize bQuit
    bQuit = false;
}

void MyFrame::OnIncreaseState(wxCommandEvent &event)
{
    c.PingServer();
}

void MyFrame::OnMessageAll(wxCommandEvent &event)
{
    c.MessageAll();
}

void MyFrame::BackgroundThread()
{
    while (!bQuit)
    {
        if (c.IsConnected())
        {
            if (!c.Incoming().empty())
            {

                auto msg = c.Incoming().pop_front().msg;
                switch (msg.header.id)
                {
                case CustomMsgTypes::ServerAccept:
                {
                    // Server has responded to a ping request
                    std::cout << "Server Accepted Connection\n";
                }
                break;

                case CustomMsgTypes::ServerPing:
                {
                    // Server has responded to a ping request
                    std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout << "Ping: " << std::chrono::duration<double>(timeNow - timeThen).count() << "\n";
                }
                break;

                case CustomMsgTypes::ServerMessage:
                {
                    // Server has responded to a ping request
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "Hello from [" << clientID << "]\n";
                }
                break;
                }
            }
        }
        else
        {
            std::cout << "Server Down\n";
            bQuit = true;
        }
    }
}

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame("State Increase Client", wxPoint(50, 50), wxSize(400, 300));

    // Show the frame on the main thread
    frame->Show(true);

    return true;
}

IMPLEMENT_APP(MyApp)
