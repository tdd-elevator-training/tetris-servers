#include <gtest/gtest.h>

#include <TetrisLib/MessageEncoding.h>

using namespace tetris;

TEST(MessageEncoding, ShouldDecodeTextWhenEncodedText)
{
  const std::string text = "abcXYZ123";

  auto bytes = StringToBytes(text);
  auto decoded = StringFromBytes(bytes);

  EXPECT_EQ(text, decoded);
}