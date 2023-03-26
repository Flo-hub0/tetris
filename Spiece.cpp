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
/*
void
Spiece::RotateCW()
{
  if (this->footprint[0][0] == this->footprint[0][1]) {
    // la piece est horizontale
    if (this->footprint[1][1]-this->footprint[1][0] > 1) {
      // la piece est alignee avec Oy => on la tourne d'un quart de tour
      this->shape[0].x++;
      this->shape[0].y++;
      this->shape[3].x--;
      this->shape[3].y--;
    } else {
      // la piece est alignee avec Oz => on la tourne d'un quart de tour
      this->shape[2].x++;
      this->shape[2].y++;
      this->shape[3].x++;
      this->shape[3].y++;
    }
  } else {
    if (this->footprint[2][0] == this->footprint[2][1]) {
      // la piece est dans le plan xOy
      if (this->footprint[0][1]-this->footprint[0][0] > 1) {
	// la piece est alignee sur Oy
	this->shape[0].x++;
	this->shape[0].y++;
	this->shape[2].x--;
	this->shape[2].y++;
	this->shape[3].x -= 2;
      } else {
	// la piece est alignee sur Ox
	this->shape[0].x--;
	this->shape[0].y--;
	this->shape[2].x++;
	this->shape[2].y--;
	this->shape[3].x += 2;
      }
    } else {
      // la piece est dans le plan xOz
      if (this->footprint[2][1]-this->footprint[2][0] > 1) {
	// la piece est alignee sur Oz
	this->shape[0].z--;
	this->shape[0].x--;
	this->shape[2].z++;
	this->shape[2].x--;
	this->shape[3].z += 2;
      } else {
	// la piece est alignee sur Ox
	this->shape[0].z++;
	this->shape[0].x++;
	this->shape[2].z--;
	this->shape[2].x++;
	this->shape[3].z -= 2;
      }
  }    
}

void
Spiece::RotateCCW()
{
  // la piece etant symetrique, la tourner d'un quart de tour dans un sens ou dans l'autre est equivalent
  this->RotateCW();
}

void
Spiece::RotateForward()
{
  // to do
}

void
Spiece::RotateBackward()
{
  // la piece etant symetrique, la tourner d'un quart de tour dans un sens ou dans l'autre est equivalent
  this->RotateForward();
}
*/
