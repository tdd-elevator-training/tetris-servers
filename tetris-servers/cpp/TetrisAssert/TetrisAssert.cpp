#include <gtest/gtest.h>

#include <TetrisLib/IPieceController.h>
#include <TetrisLib/ISolver.h>
#include <TetrisLib/Problem.h>

#include "TetrisAssert.h"

namespace
{
  class EncodingController
    : public tetris::IPieceController
  {
  public:
    virtual void Left() override 
    {
      AppendCode('L');
    }
    virtual void Right() override 
    {
      AppendCode('R');
    }
    virtual void Rotate() override 
    {
      AppendCode('O');
    }
    virtual void Drop() override 
    {
      AppendCode('D');
    }

    std::string GetCode() const
    {
      return code_;
    }

  private:
    void AppendCode(char code)
    {
      code_ += code;
    }

  private:
    std::string code_;
  };

  size_t GetSafeYPosition(const tetris::Well &well)
  {
    return well.GetHeight() + 4;  // 4 cells is the height of tallest figure - the 'I'
  }
}

void tetris::EXPECT_SOLVE(const std::string &solution, tetris::ISolver &solver, const tetris::Problem &problem)
{
  EXPECT_EQ(solution, EncodeSolution(solver, problem));
}

void tetris::EXPECT_SOLVE(const std::string &solution, tetris::ISolver &solver, tetris::PieceType piece, size_t piece_x, const std::string &well_str, size_t piece_y /*= 0*/)
{
  Well well = DecodeWell(well_str);
  EXPECT_SOLVE(solution, solver, tetris::Problem(well, piece, piece_x, piece_y ? piece_y : GetSafeYPosition(well)));
}

std::string tetris::EncodeSolution(tetris::ISolver &solver, const tetris::Problem &problem)
{
  EncodingController controller;
  solver.Solve(controller, problem);
  return controller.GetCode();
}

tetris::Well tetris::DecodeWell(const std::string &well_str)
{
  if (well_str.empty())
    throw std::invalid_argument("empty string");

  if (well_str.size() < 2 || well_str[0] != '|' || well_str[well_str.size() - 1] != '|')
    throw std::invalid_argument("malformed string - some walls are missing");

  std::string::size_type right_wall = well_str.size() - 1;
  std::string::size_type left_wall = well_str.rfind('|', right_wall - 1);
  if (left_wall == std::string::npos || right_wall == std::string::npos || left_wall >= right_wall)
    throw std::logic_error("bad walls");

  size_t width = right_wall - left_wall - 1;
  if (width == 0)
    throw std::invalid_argument("well can't have zero width");

  if (well_str.size() % (width + 2) != 0)
    throw std::invalid_argument("found rows of unequal length");

  size_t height = well_str.size() / (width + 2);
  Well well(width, height);

  for (size_t y = 0; y < height; ++y)
  {
    if (well_str[left_wall] != '|' || well_str[right_wall] != '|')
      throw std::invalid_argument("some walls are missing");

    for (size_t x = 0; x < width; ++x)
      if (!isspace(well_str[left_wall + 1 + x]))
        well.OccupyCell(x, y);

    left_wall -= width + 2;
    right_wall -= width + 2;
  }

  return well;
}

