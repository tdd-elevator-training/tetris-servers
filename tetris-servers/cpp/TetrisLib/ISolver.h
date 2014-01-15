#pragma once

#include "API.h"

namespace tetris
{

  struct IPieceController;
  class Problem;

  /**
    Interface ISolver - solves given problem and expresses solution via controller
  */
  struct TETRIS_API ISolver
  {
    virtual ~ISolver() {}

    virtual void Solve(IPieceController &controller, const Problem &problem) = 0;
  };

}