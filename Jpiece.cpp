#include <Jpiece.h>

Jpiece::Jpiece()
{
  this->SetShape();
}

Jpiece &
Jpiece::operator=(Jpiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Jpiece::ShapeName() const
{
  return "Jpiece";
}

void
Jpiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
