#include <gtest/gtest.h>

#include <TetrisLib/WebSocketEndPoint.h>

using namespace tetris;

TEST(WebSocketEndPoint, ShouldThrowWhenConstructingWithEmptyURL)
{
  EXPECT_THROW(WebSocketEndPoint("", "user"), std::invalid_argument);
}

TEST(WebSocketEndPoint, ShouldThrowWhenConstructingWithEmptyUserName)
{
  EXPECT_THROW(WebSocketEndPoint("ws://qwe", ""), std::invalid_argument);
}

TEST(WebSocketEndPoint, ShouldThrowWhenConstructingWithWrongProtocol)
{
  EXPECT_THROW(WebSocketEndPoint("http://qwe", "user"), std::invalid_argument);
}

