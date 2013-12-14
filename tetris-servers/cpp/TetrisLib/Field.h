#pragma once

#include <vector>

#include "API.h"
#include "IField.h"

namespace tetris
{

  /**
    Class Field - default implementation of interface IField
  */
  class TETRIS_API Field
    : public IField
  {
  public:
    /// Constructor
    /// will throw if either width or height is zero
    Field(size_t width, size_t height);

    Field(const Field &);

    Field &operator=(const Field &);

    ~Field();

    /// @see IField::GetWidth
    virtual size_t GetWidth() const override;

    /// @see IField::GetHeight
    virtual size_t GetHeight() const override;

    /// @see IField::IsCellFree
    virtual bool IsCellFree(size_t x, size_t y) const override;

    /// @see IField::OccupyCell
    virtual void OccupyCell(size_t x, size_t y) override;

    /// @see IField::FreeCell
    virtual void FreeCell(size_t x, size_t y) override;

    /// Convenience method, it's value is always opposite to IsCellFree()
    bool IsCellOccupied(size_t x, size_t y) const;

  private:
    class Impl;
    Impl *p_impl_;
  };

}