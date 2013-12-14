#pragma once

#include <TetrisLib/ISolver.h>

#include "API.h"

class MYSOLVER_API MySolver
  : public tetris::ISolver
{
public:
  virtual void Solve(tetris::IPieceController &controller, const tetris::Problem &problem) override;
};