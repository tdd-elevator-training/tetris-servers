#pragma once

#include <string>

#include <TetrisLib/PieceType.h>
#include <TetrisLib/Well.h>

#include "API.h"

namespace tetris
{
  struct ISolver;
  class Problem;

  /**
    GoogleTest-compatible assertion specialized for checking solver's response to a given tetris problem.

    @param solution - encoded solution to check against, @see EncodeSolution
  */
  TETRIS_ASSERT_API void EXPECT_SOLVE(const std::string &solution, ISolver &solver, const Problem &i_problem);

  /**
    GoogleTest-compatible assertion specialized for checking solver's response to given well and piece.

    By default, only the x-position of the piece is required, the y-position is taken as the height of the well height plus 4 
    to allow piece movement freely.
    @param solution - encoded solution to check against, @see EncodeSolution
    @param piece - given piece
    @param piece_x - x-position of the piece
    @param well - encoded state of the well, @see DecodeWell
    @param piece_y (optional) - you may specify y-position of the piece if default is not what you want.
  */
  TETRIS_ASSERT_API void EXPECT_SOLVE(const std::string &solution, ISolver &solver, PieceType piece, size_t piece_x, const std::string &well_str, size_t piece_y = 0);

  /**
    Creates well object from given string which follows the notation below.

    Left and right walls of the well must be encoded with '|' symbol, 
    and any non-space symbol between walls designates an occupied cell. 
    Important: beginning of the string encodes the top row of the well, the end of the string - the bottom of the well.
  */
  TETRIS_ASSERT_API Well DecodeWell(const std::string &well_str);

  /**
    Encodes solution of a problem in the notation: L=left, R=right, O=rotate, D=drop.
    For example, two times left and drop should be encoded as "LLD"
  */
  TETRIS_ASSERT_API std::string EncodeSolution(ISolver &solver, const Problem &problem);
}