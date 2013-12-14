#include <gtest/gtest.h>

#include <TetrisLib/Field.h>

using namespace tetris;

TEST(Field, ConstructorShouldThrowWhenEighterDimensionIsZero)
{
  EXPECT_THROW(Field(0, 10), std::invalid_argument);
  EXPECT_THROW(Field(10, 0), std::invalid_argument);
}

TEST(Field, ShouldBeEmptyAfterConstruction)
{
  Field field(3, 4);

  for (size_t x = 0; x < field.GetWidth(); ++x)
    for (size_t y = 0; y < field.GetHeight(); ++y)
    {
      EXPECT_TRUE(field.IsCellFree(x, y));
      EXPECT_FALSE(field.IsCellOccupied(x, y));
    }
}

TEST(Field, ShouldBeNotFreeWhenCellIsOccupied)
{
  Field field(3, 4);

  field.OccupyCell(1, 2);

  EXPECT_TRUE(field.IsCellOccupied(1, 2));
}

TEST(Field, ShouldThrowWhenXOrYIsOutOfBounds)
{
  Field field(3, 4);

  EXPECT_THROW(field.IsCellFree(3, 3), std::invalid_argument);
  EXPECT_THROW(field.IsCellFree(0, 4), std::invalid_argument);
}

TEST(Field, ShouldBeFreeWhenFreed)
{
  Field field(3, 4);
  field.OccupyCell(1, 2);

  field.FreeCell(1, 2);

  EXPECT_TRUE(field.IsCellFree(1, 2));
}