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

/*
void
Ipiece::RotateCW()
{
  if (this->footprint[0][0] == this->footprint[0][1]) {
    // la piece est horizontale
    if (this->footprint[1][0] == this->footprint[1][1]) {
      // la piece est alignee avec Oz => elle est invariante par rapport a cette rotation
    } else {
      // la piece est alignee avec Oy => on la tourne d'un quart de tour
      this->shape[0].x += 2;
      this->shape[0].y += 2;
      this->shape[1].x++;
      this->shape[1].y++;
      this->shape[3].x--;
      this->shape[3].y--;
    }
  } else {
    // la piece est alignee avec Ox => on la tourne d'un quart de tour
    this->shape[0].x -= 2;
    this->shape[0].y -= 2;
    this->shape[1].x--;
    this->shape[1].y--;
    this->shape[3].x++;
    this->shape[3].y++;
  }    
}

void
Ipiece::RotateCCW()
{
  // la piece etant symetrique, la tourner d'un quart de tour dans un sens ou dans l'autre est equivalent
  this->RotateCW();
}

void
Ipiece::RotateForward()
{
  if (this->footprint[0][0] == this->footprint[0][1]) {
    // la piece est horizontale
    if (this->footprint[1][0] == this->footprint[1][1]) {
      // la piece est alignee avec Oz => on la tourne d'un quart de tour
      this->shape[0].y -= 2;
      this->shape[0].z -= 2;
      this->shape[1].y--;
      this->shape[1].z--;
      this->shape[3].y++;
      this->shape[3].z++;
    } else {
      // la piece est alignee avec Oy => elle est invariante par rapport a cette rotation
    }
  } else {
    // la piece est alignee avec Ox => on la tourne d'un quart de tour
    this->shape[0].y += 2;
    this->shape[0].z += 2;
    this->shape[1].y++;
    this->shape[1].z++;
    this->shape[3].y--;
    this->shape[3].z--;
  }    
}

void
Ipiece::RotateBackward()
{
  // la piece etant symetrique, la tourner d'un quart de tour dans un sens ou dans l'autre est equivalent
  this->RotateForward();
}
*/
