#include <Ipiece.h>

Ipiece::Ipiece()
{
  this->SetShape();
}

Ipiece &
Ipiece::operator=(Ipiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Ipiece::ShapeName() const
{
  return "Ipiece";
}

void
Ipiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
