#include "Event/Event.h"
#include <gtest/gtest.h>

using namespace DarrJorge;

TEST(EventTest, ShouldCallSubscriberWhenInvoked)
{
    Event<int> event;
    int received{0};
    event.add([&received](int value){received = value;});

    EXPECT_EQ(received, 0);
    event.invoke(42);
    EXPECT_EQ(received, 42);
}

TEST(EventTest, ShouldStopDeliveryWhenSubcriberRemoved)
{
    Event<int> event;
    int callCount{0};
    const auto handle = event.add([&callCount](int){++callCount;});

    EXPECT_EQ(callCount, 0);
    event.invoke(42);
    EXPECT_EQ(callCount, 1);
    event.invoke(42);
    EXPECT_EQ(callCount, 2);

    event.remove(handle);
    event.invoke(42);
    EXPECT_EQ(callCount, 2);
}

namespace
{
struct Listener
{
    int value{0};
    void onValue(int val) { value = val;}
};
}

TEST(EventTest, ShouldCallMemberFunctionWhenSubscribed)
{
    Event<int> event;
    Listener listener;
    EXPECT_EQ(listener.value, 0);

    event.add(&listener, &Listener::onValue);
    event.invoke(55);

    EXPECT_EQ(listener.value, 55);
}