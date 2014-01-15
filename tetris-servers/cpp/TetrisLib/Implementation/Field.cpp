#include <stdexcept>

#include "../Field.h"

using namespace tetris;

class Field::Impl
{
public:
  Impl(size_t width, size_t height)
    : width_(width)
    , height_(height)
  {
    if (width == 0 || height == 0)
      throw std::invalid_argument("none of dimensions can be zero");

    matrix_.resize(width * height);
  }

  size_t GetWidth() const
  {
    return width_;
  }

  size_t GetHeight() const
  {
    return height_;
  }

  bool IsCellFree(size_t x, size_t y) const
  {
    return !matrix_[GetIndex(x, y)];
  }

  void OccupyCell(size_t x, size_t y)
  {
    matrix_[GetIndex(x, y)] = true;
  }

  void FreeCell(size_t x, size_t y) 
  {
    matrix_[GetIndex(x, y)] = false;
  }

  bool IsCellOccupied(size_t x, size_t y) const
  {
    return !IsCellFree(x, y);
  }

private:
  size_t GetIndex(size_t x, size_t y) const
  {
    if (x >= width_ || y >= height_)
      throw std::invalid_argument("position is out of bounds");

    return y * width_ + x;
  }

private:
  size_t width_;
  size_t height_;
  std::vector<bool> matrix_;
};

Field::Field(size_t width, size_t height)
  : p_impl_(new Impl(width, height))
{
}

Field::~Field()
{
}

size_t Field::GetWidth() const 
{
  return p_impl_->GetWidth();
}

size_t Field::GetHeight() const 
{
  return p_impl_->GetHeight();
}

bool Field::IsCellFree(size_t x, size_t y) const 
{
  return p_impl_->IsCellFree(x, y);
}

void tetris::Field::OccupyCell(size_t x, size_t y)
{
  p_impl_->OccupyCell(x, y);
}

void tetris::Field::FreeCell(size_t x, size_t y)
{
  p_impl_->FreeCell(x, y);
}

bool Field::IsCellOccupied(size_t x, size_t y) const
{
  return p_impl_->IsCellOccupied(x, y);
}

Field::Field(const Field &right)
  : p_impl_(new Impl(*right.p_impl_))
{
}

Field &Field::operator=(const Field &right)
{
  delete p_impl_;
  p_impl_ = new Impl(*right.p_impl_);
  return *this;
}