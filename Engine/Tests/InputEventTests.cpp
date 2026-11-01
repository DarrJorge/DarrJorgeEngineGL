#include "Event/InputEvent.h"
#include "Event/InputEventFormat.h"
#include <gtest/gtest.h>
#include <format>

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

TEST(InputEventTest, DefaultConstructedEventShouldBeInherit)
{
    EXPECT_EQ(InputEvent{}.type(), EventType::None);
    EXPECT_EQ(KeyEventData{}.key, Key::None);
    EXPECT_EQ(KeyEventData{}.action, KeyAction::None);
    EXPECT_EQ(MouseButtonEventData{}.button, MouseButton::None);
    EXPECT_EQ(MouseButtonEventData{}.action, KeyAction::None);
}

TEST(InputEventTest, ShouldConvertEnumsToStringCorrectly)
{
    EXPECT_EQ(toString(Key::None), "None");
}

TEST(InputEventTest, ShouldFormatEnumsWithStdFormat)
{
    // TODO not compile with apple clang 16.0.0
    //EXPECT_EQ(std::format("{}", Key::KeyA), "KeyA");
}