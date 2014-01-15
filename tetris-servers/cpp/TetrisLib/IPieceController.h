#pragma once

#include "API.h"

namespace tetris
{

  /**
    Interface IPieceController - controls current piece
  */
  struct TETRIS_API IPieceController
  {
    virtual ~IPieceController() {}

    /// Move the piece one cell left
    virtual void Left() = 0;

    /// Move the piece one cell right
    virtual void Right() = 0;

    /// Rotate the piece 90 degree clockwise (see contest documentation for details)
    virtual void Rotate() = 0;

    /// Drop the piece
    virtual void Drop() = 0;
  };

}