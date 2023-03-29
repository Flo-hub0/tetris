#include <Field.h>
#include <cassert>

// Calcul de l'indice d'une case dans la grille a partir d'une position
#define index(i,j,k) ((i)*this->dimensions[1]*this->dimensions[2]+(j)*this->dimensions[2]+(k))

Field::Field(vector<int> dimensions, PieceFactory factory)
{
  this->SetDimensions(dimensions);
  // on alloue 3 niveaux supplementaires car si une piece est tournee des le depart, elle peut depasser au dela de la grille
  this->grid.resize((dimensions[0]+3)*dimensions[1]*dimensions[2], false);
  this->active = NULL;
  this->factory = factory;
  this->level = this->score = 0;
  this->isover = false;
}

Field::Field(Field &other)
{
  this->dimensions = other.dimensions;
  this->grid = other.grid;
  this->active = other.active;
  this->factory = other.factory;
  this->level = other.level;
  this->score = other.score;
  this->isover = other.isover;
}

Field::~Field()
{
  this->dimensions.clear();
  this->grid.clear();
  if (this->active != NULL)
    delete this->active;
}

Field &
Field::operator=(Field &other)
{
  this->dimensions = other.dimensions;
  this->grid = other.grid;
  this->active = other.active;
  this->factory = other.factory;
  this->level = other.level;
  this->score = other.score;
  this->isover = other.isover;
  return *this;
}

void
Field::SetDimensions(vector<int> dimensions)
{
  assert((dimensions.size() == 2 && dimensions[0]>0 && dimensions[1]>0) ||
	 (dimensions.size() == 3 && dimensions[0]>0 && dimensions[1]>0 && dimensions[2]>0));
  this->dimensions = dimensions;
  if (this->dimensions.size() == 2)
    this->dimensions.push_back(1);
  this->floor_size = this->dimensions[1] * this->dimensions[2];
}

void
Field::SetLevel(int level)
{
  assert(level >= 0);
  this->level = level;
}

void
Field::Left()
{
  if (this->isover)
    return;
  this->active->Left();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::Right()
{
  if (this->isover)
    return;
  this->active->Right();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::Forward()
{
  if (this->isover)
    return;
  this->active->Forward();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::Backward()
{
  if (this->isover)
    return;
  this->active->Backward();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::RotateCW()
{
  if (this->isover)
    return;
  this->active->RotateCW();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::RotateCCW()
{
  if (this->isover)
    return;
  this->active->RotateCCW();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::RotateForward()
{
  if (this->isover)
    return;
  this->active->RotateForward();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::RotateBackward()
{
  if (this->isover)
    return;
  this->active->RotateBackward();
  if (!this->CheckValidity())
    this->active->Undo();
}

void
Field::Reset()
{
  this->grid.assign(this->grid.size(), false);
  this->level = this->score = 0;
  this->isover = false;
  if (this->active != NULL)
    delete this->active;
}

void
Field::Start()
{
  this->Reset();
  this->active = this->factory.NewPiece();
  this->active->SetTopCenter(this->dimensions);
}

void
Field::Update()
{
  if (this->isover)
    return;
  this->active->Down();
  cout << *this->active;
  if (!this->CheckValidity()) {
    this->active->Undo();
    // si la piece depasse au dela de la hauteur de la grille, le jeu est termine
    if (this->active->Footprint()[0][1] >= this->dimensions[0]) {
      this->isover = true;
      return;
    }
    // la piece active est desormais figee dans sa position
    for (auto p : this->active->Positions())
      this->grid[index(p.x,p.y,p.z)] = true;
    // on detruit les eventuelles lignes qui ont ete completees
    vector<int> to_delete;
    // on parcourt de haut en bas, ce qui facilitera le traitement de suppression de lignes
    for (int i=this->active->Footprint()[0][1] ; i>=this->active->Footprint()[0][0] ; i--)
      if (this->IsFilled(i))
	to_delete.push_back(i);
    // on met a jour le score
    int p = to_delete.size() == 0 ? 0 : to_delete.size() == 1 ? 40 : to_delete.size() == 2 ? 100 : to_delete.size() == 3 ? 300 : 1200;
    this->score += p * (this->level + 1);
    // on supprime les lignes completes
    for (int n : to_delete) {
      size_t endi = this->dimensions[0] * this->floor_size;
      for (size_t i=index(n,0,0) ; i<endi ; i++)
	this->grid[i] = this->grid[i+this->floor_size];
    }
    // on genere une nouvelle piece active
    delete this->active;
    this->active = this->factory.NewPiece();
    this->active->SetTopCenter(this->dimensions);
    // detection de la fin du jeu
    if (!this->CheckValidity()) {
      if (this->active != NULL) {
	delete this->active;
	this->active = NULL;
      }
      this->isover = true;
    }
  }
}

bool
Field::CheckValidity() const
{
  if (this->active->Footprint()[0][0] < 0 || this->active->Footprint()[0][1] >= this->dimensions[0]+3)
    return false;
  for (int i=1 ; i<3 ; i++)
    if (this->active->Footprint()[i][0] < 0 || this->active->Footprint()[i][1] >= this->dimensions[i])
      return false;
  for (auto i : this->active->Positions())
    if (this->grid[index(i.x,i.y,i.z)])
      return false;
  return true;
}

bool
Field::IsFilled(int n) const
{
  n *= this->floor_size;
  for (int i=0 ; i<this->floor_size ; i++)
    if (!this->grid[i+n])
      return false;
  return true;
}
  
ostream &
operator<<(ostream &os, const Field &f)
{
  if (f.GetDimensions()[2] == 1)
    os << "Plateau de " << f.GetDimensions()[0] << "x" << f.GetDimensions()[1] << endl;
  else
    os << "Plateau de " << f.GetDimensions()[0] << "x" << f.GetDimensions()[1] << "x" << f.GetDimensions()[2] << endl << endl;
  return os;
}
