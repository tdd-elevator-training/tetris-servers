#include "../Problem.h"

using namespace tetris;

Problem::Problem(const Well &well, PieceType piece, size_t x, size_t y)
  : well_(well)
  , piece_(piece)
  , piece_x_(x)
  , piece_y_(y)
{
}

const Well &Problem::GetWell() const
{
  return well_;
}

PieceType Problem::GetPiece() const
{
  return piece_;
}

size_t Problem::GetPieceX() const
{
  return piece_x_;
}

size_t Problem::GetPieceY() const
{
  return piece_y_;
}