#include <Lpiece.h>

Lpiece::Lpiece()
{
  this->SetShape();
}

Lpiece &
Lpiece::operator=(Lpiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Lpiece::ShapeName() const
{
  return "Lpiece";
}

void
Lpiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
