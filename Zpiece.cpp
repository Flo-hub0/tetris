#include <Zpiece.h>

Zpiece::Zpiece()
{
  this->SetShape();
}

Zpiece &
Zpiece::operator=(Zpiece &other)
{
  Piece::operator=(other);
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Zpiece::ShapeName() const
{
  return "Zpiece";
}

void
Zpiece::SetShape()
{
  this->gravity = center_of_gravity;
  for (auto p : this->positions)
    this->shape.push_back(p);
  this->ComputeFootprint();
}
