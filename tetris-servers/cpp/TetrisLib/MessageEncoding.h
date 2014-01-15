#pragma once

#include <string>
#include <vector>

#include "API.h"

namespace tetris
{

  /// Encodes given message into array of bytes for transfer over the network
  TETRIS_API std::vector<char> StringToBytes(const std::string &string);

  /// Decodes message from array of bytes that came over the network
  TETRIS_API std::string StringFromBytes(const std::vector<char> &bytes);

}