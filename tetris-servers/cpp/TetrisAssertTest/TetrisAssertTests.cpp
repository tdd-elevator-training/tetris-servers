#include <gmock/gmock.h>

#include <TetrisAssert/TetrisAssert.h>
#include <TetrisLib/IPieceController.h>
#include <TetrisLib/ISolver.h>
#include <TetrisLib/Problem.h>
#include <TetrisLib/Well.h>

using namespace tetris;

TEST(TetrisAssert, ShouldEncodeAllCommands)
{
  class FakeSolver: public ISolver
  {
  public:
    virtual void Solve(IPieceController &controller, const Problem &problem) override
    {
      controller.Left();
      controller.Right();
      controller.Rotate();
      controller.Drop();
    }
  } fake_solver;

  std::string encoded_solution = EncodeSolution(fake_solver, Problem(Well(1, 1), PIECE_I, 0, 0));

  EXPECT_EQ("LROD", encoded_solution);
}

TEST(TetrisAssert, ShouldEncodeRepeatingCommands)
{
  class FakeSolver: public ISolver
  {
  public:
    virtual void Solve(IPieceController &controller, const Problem &problem) override
    {
      controller.Left();
      controller.Left();
    }
  } fake_solver;

  std::string encoded_solution = EncodeSolution(fake_solver, Problem(Well(1, 1), PIECE_I, 0, 0));

  EXPECT_EQ("LL", encoded_solution);
}

TEST(TetrisAssert, ShouldDecodeWell)
{
  std::string well_str = 
    "|*   **|"
    "|*** **|";

  Well well = DecodeWell(well_str);

  ASSERT_EQ(6, well.GetWidth());
  ASSERT_GE(2u, well.GetHeight()); // could be higher then two

  EXPECT_TRUE(well.IsCellOccupied(0, 0));
  EXPECT_TRUE(well.IsCellFree(3, 0));
  EXPECT_TRUE(well.IsCellOccupied(5, 1));
  EXPECT_TRUE(well.IsCellFree(1, 1));
}

TEST(TetrisAssert, ShouldThrowWhenDecodingWellFromEmptyString)
{
  EXPECT_THROW(DecodeWell(""), std::invalid_argument);
}

TEST(TetrisAssert, ShouldThrowWhenDecodingWellFromStringWithMissingWalls)
{
  EXPECT_THROW(DecodeWell("** *|"), std::invalid_argument);
  EXPECT_THROW(DecodeWell("|** *"), std::invalid_argument);
}

TEST(TetrisAssert, ShouldThrowWhenDecodingZeroWidthWell)
{
  EXPECT_THROW(DecodeWell("||"), std::invalid_argument);
}

TEST(TetrisAssert, ShouldThrowWhenDecodingRowsOfDifferentLength)
{
  EXPECT_THROW(DecodeWell("|*||**|"), std::invalid_argument);
}