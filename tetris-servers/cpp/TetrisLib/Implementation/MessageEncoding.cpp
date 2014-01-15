#include "../MessageEncoding.h"

static_assert(sizeof(char) == 1, "char is a byte");

std::vector<char> tetris::StringToBytes(const std::string &string)
{
  return std::vector<char>(string.cbegin(), string.cend());
}

std::string tetris::StringFromBytes(const std::vector<char> &bytes)
{
  return std::string(bytes.cbegin(), bytes.cend());
}
