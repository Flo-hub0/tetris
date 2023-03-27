#include <Tpiece.h>

Tpiece::Tpiece()
{
  this->SetShape();
}

Tpiece &
Tpiece::operator=(Tpiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Tpiece::ShapeName() const
{
  return "Tpiece";
}

void
Tpiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
