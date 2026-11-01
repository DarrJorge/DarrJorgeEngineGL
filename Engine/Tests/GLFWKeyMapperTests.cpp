#include "Window/GLFW/GLFWKeyMapper.h"
#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

using namespace DarrJorge;

TEST(GLFWKeyMapperTest, ShouldMapKeysCorrectly)
{
    EXPECT_EQ(KeyMapper::toKey(GLFW_KEY_ESCAPE) , Key::Esc);
    EXPECT_EQ(KeyMapper::toMouseButton(GLFW_MOUSE_BUTTON_LEFT) , MouseButton::Left);
}

TEST(GLFWKeyMapperTest, ShouldReturnNoneForUknown)
{
    EXPECT_EQ(KeyMapper::toKey(GLFW_KEY_UNKNOWN) , Key::Unknown);
    EXPECT_EQ(KeyMapper::toKey(-1), Key::Unknown);
    EXPECT_EQ(KeyMapper::toKey(9999), Key::Unknown);
}