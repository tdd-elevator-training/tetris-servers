#include <TetrisLib/IPieceController.h>
#include <TetrisLib/Problem.h>

#include "MySolver.h"

using namespace tetris;

void MySolver::Solve(tetris::IPieceController &controller, const tetris::Problem &problem)
{
  controller.Left();
}

