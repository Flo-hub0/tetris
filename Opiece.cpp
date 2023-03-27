#include <Opiece.h>

Opiece::Opiece()
{
  this->SetShape();
}

Opiece &
Opiece::operator=(Opiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Opiece::ShapeName() const
{
  return "Opiece";
}

void
Opiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
