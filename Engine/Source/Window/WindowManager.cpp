#include "WindowManager.h"
#include "Log/Log.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogWindowManager);

void WindowManager::cleanupClosedWindows()
{
    auto it = m_windows.begin();
    while (it != m_windows.end())
    {
        if (it->second->shouldClose())
        {
            LOG(LogWindowManager, Display, "Removing window with id {}", it->first.value);
            it = m_windows.erase(it);
            continue;
        }
        it++;
    }
}

const std::unordered_map<WindowId, std::shared_ptr<IWindow>>& WindowManager::windows() const
{
    return m_windows;
}

bool WindowManager::allWindowsClosed() const
{
    return m_windows.empty();
}

std::shared_ptr<IWindow> WindowManager::getWindowById(WindowId id) const
{
    const auto it = m_windows.find(id);
    return it != m_windows.end() ? it->second : nullptr;
}
