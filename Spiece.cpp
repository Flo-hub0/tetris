#include <Spiece.h>

Spiece::Spiece()
{
  this->SetShape();
}

Spiece &
Spiece::operator=(Spiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Spiece::ShapeName() const
{
  return "Spiece";
}

void
Spiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
