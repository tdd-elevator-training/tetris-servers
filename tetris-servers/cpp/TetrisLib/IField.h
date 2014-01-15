#pragma once

#include "API.h"

namespace tetris
{

  /** 
    Interface IField - represents rectangular field of cells.
    Each cell can be either free or occupied.
    IMPORTANT: zero y means bottom of the field
  */
  struct TETRIS_API IField
  {
    virtual ~IField() {}

    /// Returns width of the field
    virtual size_t GetWidth() const = 0;

    /// Returns height of the field
    virtual size_t GetHeight() const = 0;

    /// Tests whether cell is free
    virtual bool IsCellFree(size_t x, size_t y) const = 0;
    
    /// Marks cell as occupied
    virtual void OccupyCell(size_t x, size_t y) = 0;

    /// Marks cell as free
    virtual void FreeCell(size_t x, size_t y) = 0;
  };

}