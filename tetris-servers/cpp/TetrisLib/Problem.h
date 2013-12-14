#pragma once

#include "API.h"
#include "PieceType.h"
#include "Well.h"

namespace tetris
{

  /**
    Compound class Problem stores all information about problem to solve.
  */
  class TETRIS_API Problem
  {
  public:
    Problem(const Well &well, PieceType piece, size_t x, size_t y);

    /// Returns tetris well
    const Well &GetWell() const;

    /// Returns current piece
    PieceType GetPiece() const;

    /// Returns the x-coordinate of the current piece
    size_t GetPieceX() const;

    /// Returns the y-coordinate of the current piece
    size_t GetPieceY() const;

  private:
    Well well_;
    PieceType piece_;
    size_t piece_x_;
    size_t piece_y_;
  };

}