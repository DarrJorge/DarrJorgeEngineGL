#include "WinAPIWindow.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogWinAPIWindow);

WinAPIWindow::WinAPIWindow(const WindowSettings& settings, HINSTANCE hInstance, const std::string& className)
{
    m_window = CreateWindowEx(   //
        0,                       //
        className.c_str(),       //
        settings.title.c_str(),  //
        WS_OVERLAPPEDWINDOW,     //
        settings.x,              //
        settings.y,              //
        settings.width,          //
        settings.height,         //
        nullptr, nullptr,        //
        hInstance,               //
        nullptr);

    if (!m_window)
    {
        LOG(LogWinAPIWindow, Error, "Failed to create WinAPI window");
        return;
    }

    ShowWindow(m_window, SW_SHOW);
    UpdateWindow(m_window);
}

WinAPIWindow::~WinAPIWindow()
{
    if (m_window)
    {
        DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void WinAPIWindow::setTitle(const std::string& title)
{
    if (!m_window) return;
    SetWindowText(m_window, title.c_str());
}

void WinAPIWindow::setWindowForCurrentContext() {}

bool WinAPIWindow::isValid() const
{
    return m_window != nullptr;
}

bool WinAPIWindow::shouldClose() const
{
    if (!m_window) return true;
    return false;
}

void WinAPIWindow::swapBuffers() {}
