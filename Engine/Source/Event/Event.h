#pragma once

#include <string>
#include <Log/Log.h>
#include "InputEvent.h"

using namespace DarrJorge;

DEFINE_LOG_CATEGORY_STATIC(LogEvent);

namespace DarrJorge
{
template <typename... Args> class Event
{
public:
    void invoke(Args... args)
    {
        auto printEvent = [](const InputEvent& event)
        {
            std::string eventTypeStr;
            switch (event.type)
            {
                case EventType::KeyPress: eventTypeStr = "KeyPress"; break;
                case EventType::MouseButton: eventTypeStr = "MouseButton"; break;
                case EventType::MouseMove: eventTypeStr = "MouseMove"; break;
                case EventType::MouseScroll: eventTypeStr = "MouseScroll"; break;
                case EventType::WindowResize: eventTypeStr = "WindowResize"; break;
                case EventType::WindowClose: eventTypeStr = "WindowClose"; break;
            }

            LOG(LogEvent, Display, "Dispatch event: {}.", eventTypeStr);
        };

        (printEvent(args), ...);
    }
};
}  // namespace DarrJorge
