#include "Event/InputEvent.h"
#include <gtest/gtest.h>

using namespace DarrJorge;

TEST(InputEventTest, ShouldHoldExpectedAlternativeWhenAssigned)
{
    EventData data = WindowResizeEventData{1920, 1080};

    EXPECT_TRUE(std::holds_alternative<WindowResizeEventData>(data));
    EXPECT_FALSE(std::holds_alternative<WindowCloseEventData>(data));
    EXPECT_EQ(std::get<WindowResizeEventData>(data).width, 1920);
    EXPECT_EQ(std::get<WindowResizeEventData>(data).height, 1080);
}

TEST(InputEventTest, ShouldDefaultToMonostateWhenConstructedEmpty)
{
    const EventData data;

    EXPECT_TRUE(std::holds_alternative<std::monostate>(data));
}

TEST(InputEventTest, ShouldReturnNullWhenAccessingWrong)
{
    EventData data = WindowResizeEventData{1920, 1080};

    EXPECT_EQ(std::get_if<MouseMoveEventData>(&data), nullptr);
}

