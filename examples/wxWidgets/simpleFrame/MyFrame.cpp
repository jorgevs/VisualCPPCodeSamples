#include "MyFrame.h"

// Constructor
MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Hello World", wxPoint(30, 30), wxSize(800, 600)) {

    // Create menus
    wxMenu *menuFile = new wxMenu();
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT);

    // Create menuBar and set menus
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    // Attach the menu bar to the frame
    SetMenuBar(menuBar);

    // Create statusBar
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    // Setting a layout
    wxGridSizer *grid = new wxGridSizer(2, 2, 10, 10);

    wxButton *myButton = new wxButton(this, ID_MyButton, "Click me", wxPoint(10, 10), wxSize(150, 50));
    //grid->Add(myButton);
    grid->Add(myButton, 1, wxEXPAND | wxALL);

    // Define window properties
    this->SetSize(800, 600);
    this->SetSizer(grid);
    this->Centre();

    // Bind window events to myFrame methods
    Bind(wxEVT_MENU, [=](wxCommandEvent &) {
        wxLogMessage("Hello world from wxWidgets!");
    }, ID_Hello);

    Bind(wxEVT_MENU, [=](wxCommandEvent &) {
        wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
    }, wxID_ABOUT);

    Bind(wxEVT_MENU, [=](wxCommandEvent &) {
        Close(true);
    }, wxID_EXIT);

    Bind(wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent &) {
        wxMessageBox("Button clicked!", "Message", wxOK | wxICON_INFORMATION);
    }, ID_MyButton);
}
