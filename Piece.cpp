#include <Piece.h>
#include <cassert>

Piece::Piece()
{
  this->footprint = {{0,0},{0,0},{0,0}};
}

Piece::Piece(Piece &other)
{
  this->shape = other.shape;
  this->footprint = other.footprint;
}

Piece::~Piece()
{
  this->shape.clear();
  this->footprint.clear();
}

Piece &
Piece::operator=(Piece &other)
{
  this->shape = other.shape;
  this->footprint = other.footprint;
  return *this;
}

string
Piece::ShapeName() const
{
  return "Piece";
}

void
Piece::ComputeFootprint()

{
  assert(this->shape.size() > 3);
  auto p = this->shape[0];
  this->footprint[0][0] = this->footprint[0][1] = p.x;
  this->footprint[1][0] = this->footprint[1][1] = p.y;
  this->footprint[2][0] = this->footprint[2][1] = p.z;
  for (auto p : this->shape) {
    this->footprint[0][0] = p.x<this->footprint[0][0] ? p.x : this->footprint[0][0];
    this->footprint[1][0] = p.y<this->footprint[1][0] ? p.y : this->footprint[1][0];
    this->footprint[2][0] = p.z<this->footprint[2][0] ? p.z : this->footprint[2][0];
    this->footprint[0][1] = p.x>this->footprint[0][1] ? p.x : this->footprint[0][1];
    this->footprint[1][1] = p.y>this->footprint[1][1] ? p.y : this->footprint[1][1];
    this->footprint[2][1] = p.z>this->footprint[2][1] ? p.z : this->footprint[2][1];
  }
}

void
Piece::SaveForRestore()
{
  this->old_shape = this->shape;
  this->old_footprint = this->footprint;
}

void
Piece::SetTopCenter(vector<int> dimensions)
{
  Position shift;
  shift.x = dimensions[0] - this->footprint[0][1] - 1;
  shift.y = dimensions[1] / 2 - this->shape[this->gravity].y;
  shift.z = dimensions[2] / 2 - this->shape[this->gravity].z;
  for (auto &p : this->shape) {
    p.x += shift.x;
    p.y += shift.y;
    p.z += shift.z;
  }
  this->footprint[0][0] += shift.x;
  this->footprint[0][1] += shift.x;
  this->footprint[1][0] += shift.y;
  this->footprint[1][1] += shift.y;
  this->footprint[2][0] += shift.z;
  this->footprint[2][1] += shift.z;
}  

void
Piece::Down()
{
  this->SaveForRestore();
  for (auto &p : this->shape)
    p.x--;
  for (auto &i : this->footprint[0])
    i--;
}

void
Piece::Left()
{
  this->SaveForRestore();
  for (auto &p : this->shape)
    p.y--;
  for (auto &i : this->footprint[1])
    i--;
}

void
Piece::Right()
{
  this->SaveForRestore();
  for (auto &p : this->shape)
    p.y++;
  for (auto &i : this->footprint[1])
    i++;
}

void
Piece::Forward()
{
  this->SaveForRestore();
  for (auto &p : this->shape)
    p.z--;
  for (auto &i : this->footprint[2])
    i--;
}

void
Piece::Backward()
{
  this->SaveForRestore();
  for (auto &p : this->shape)
    p.z++;
  for (auto &i : this->footprint[2])
    i++;
}

void
Piece::RotateCW()
{
  this->SaveForRestore();
  for (auto &p : this->shape) {
    int dx = p.x - this->shape[this->gravity].x;
    int dy = p.y - this->shape[this->gravity].y;
    p.x -= dx;
    p.y -= dy;
    int k = dx;
    dx = -dy;
    dy = k;
    p.x += dx;
    p.y += dy;
  }
  this->ComputeFootprint();
}

void
Piece::RotateCCW()
{
  this->SaveForRestore();
  for (auto &p : this->shape) {
    int dx = p.x - this->shape[this->gravity].x;
    int dy = p.y - this->shape[this->gravity].y;
    p.x -= dx;
    p.y -= dy;
    int k = dx;
    dx = dy;
    dy = -k;
    p.x += dx;
    p.y += dy;
  }
  this->ComputeFootprint();
}

void
Piece::RotateForward()
{
  this->SaveForRestore();
  for (auto &p : this->shape) {
    int dx = p.x - this->shape[this->gravity].x;
    int dz = p.z - this->shape[this->gravity].z;
    p.x -= dx;
    p.z -= dz;
    int k = dx;
    dx = -dz;
    dz = k;
    p.x += dx;
    p.z += dz;
  }
  this->ComputeFootprint();
}

void
Piece::RotateBackward()
{
  this->SaveForRestore();
  for (auto &p : this->shape) {
    int dx = p.x - this->shape[this->gravity].x;
    int dz = p.z - this->shape[this->gravity].z;
    p.x -= dx;
    p.z -= dz;
    int k = dx;
    dx = dz;
    dz = -k;
    p.x += dx;
    p.z += dz;
  }
  this->ComputeFootprint();
}

void
Piece::Undo()
{
  this->shape = this->old_shape;
  this->footprint = this->old_footprint;
}

ostream &
operator<<(ostream &os, const Piece &p)
{
  os << p.ShapeName() << " : forme =";
  for (auto i : p.Positions())
    os << " ( " << i.x << " " << i.y << " " << i.z << " )";
  os << " )" << endl << string(p.ShapeName().size()+2, ' ') << " " << "encombrement = (";
  for (auto i : p.Footprint())
    os << " ( " << i[0] << " - " << i[1] << " )";
  os << endl;
  return os;
}
