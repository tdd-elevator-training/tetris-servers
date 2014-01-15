#pragma once

#include "API.h"
#include "PieceType.h"
#include "Well.h"

namespace tetris
{

  /**
    Class GameStateLoader - loads game state from the given message
  */
  class TETRIS_API GameStateLoader
  {
  public:
    explicit GameStateLoader(const std::string &message);

    ~GameStateLoader();

    /// Loads and returns the x-coordinate of the current piece
    size_t LoadX();

    /// Loads and returns the y-coordinate of the current piece
    size_t LoadY();

    /// Loads the current piece
    PieceType LoadPiece();

    /// Loads the well
    Well LoadWell();

  private:
    // non-copyable
    GameStateLoader(const GameStateLoader &);
    GameStateLoader &operator=(const GameStateLoader &);

  private:
    class Impl;
    Impl *p_impl_;
  };

}