#include "WinAPIWindowManager.h"
#include "WinAPIWindow.h"
#include "Log/Log.h"

using namespace DarrJorge;

namespace
{
const std::string windowClassName = "WinAPIWindow";
}

DEFINE_LOG_CATEGORY_STATIC(LogWinAPIWindowManager);

WinAPIWindowManager::WinAPIWindowManager()
{
    m_hInstance = GetModuleHandleW(nullptr);

    WNDCLASS wc{};
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = windowClassName.c_str();

    if (!RegisterClass(&wc))
    {
        LOG(LogWinAPIWindowManager, Error, "Failed to initialize WinAPI!");
        return;
    }

    m_initialized = true;

    LOG(LogWinAPIWindowManager, Display, "WinAPI initialized successfully!");
}

WinAPIWindowManager::~WinAPIWindowManager()
{
    m_windows.clear();

    if (m_initialized)
    {
        UnregisterClass(windowClassName.c_str(), m_hInstance);
    }

    m_initialized = false;

    LOG(LogWinAPIWindowManager, Display, "WinAPI shutdown complete!");
}

void WinAPIWindowManager::update()
{
    if (!m_initialized) return;

    MSG msg{};
    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    cleanupClosedWindows();
}

std::expected<WindowId, WindowCreationError> WinAPIWindowManager::createWindow(const WindowSettings& settings)
{
    if (!m_initialized)
    {
        LOG(LogWinAPIWindowManager, Error, "Cannot create window. WinAPI is not initialized.");
        return std::unexpected(WindowCreationError::ManagerIsNotInitialized);
    }

    auto window = std::make_shared<WinAPIWindow>(settings, m_hInstance, windowClassName);

    if (!window->isValid())
    {
        LOG(LogWinAPIWindowManager, Error, "Failed to create WinAPI window");
        return std::unexpected(WindowCreationError::CreationFailed);
    }

    const WindowId id = m_windowIdCounter++;
    m_windows[id] = window;

    LOG(LogWinAPIWindowManager, Display, "Adding window with id {}", id.value);

    return id;
}
