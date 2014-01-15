#include <memory>

#include <gtest/gtest.h>

#include <TetrisLib/GameStateLoader.h>
#include <TetrisLib/PieceType.h>
#include <TetrisLib/Well.h>

using namespace tetris;

namespace
{

  size_t GetNumberOfOccupiedCells(const Well &well)
  {
    size_t occupied = 0;

    for (size_t x = 0; x < well.GetWidth(); ++x)
      for (size_t y = 0; y < well.GetHeight(); ++y)
        if (well.IsCellOccupied(x, y))
          ++occupied;

    return occupied;
  }

}

class GameStateLoaderTest
  : public testing::Test
{
public:
  static const std::string MESSAGE;

  GameStateLoaderTest()
    : loader_(MESSAGE)
  {
  }

  GameStateLoader loader_;
};

const std::string GameStateLoaderTest::MESSAGE = "figure=O&x=4&y=12&glass=    **        **        **        **                                                                                                                                                                    &next=OOOO";

TEST_F(GameStateLoaderTest, ShouldLoadPieceWhenMessageIsOK)
{
  PieceType piece = loader_.LoadPiece();
  
  EXPECT_EQ(PIECE_O, piece);
}

TEST_F(GameStateLoaderTest, ShouldLoadXWhenMessageIsOK)
{
  size_t x = loader_.LoadX();

  EXPECT_EQ(4, x);
}

TEST_F(GameStateLoaderTest, ShouldLoadYWhenMessageIsOK)
{
  size_t y = loader_.LoadY();

  EXPECT_EQ(12, y);
}

TEST_F(GameStateLoaderTest, ShouldLoadWellWhenMessageIsOK)
{
  Well well = loader_.LoadWell();

  EXPECT_EQ(10, well.GetWidth());
  EXPECT_EQ(20, well.GetHeight());
  EXPECT_EQ(8, GetNumberOfOccupiedCells(well));
  EXPECT_TRUE(well.IsCellOccupied(4, 0));  // zero y is at bottom, not top!
}

TEST(GameStateLoader, ShouldThrowWhenMessageIsNotOK)
{
  GameStateLoader loader("figure=O&y=12&glass=    **");

  EXPECT_THROW(loader.LoadX(), std::runtime_error);
}