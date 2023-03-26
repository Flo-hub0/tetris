#include <PieceFactory.h>

PieceFactory::PieceFactory()
{
  srand(time(NULL));
}

Piece *
PieceFactory::NewPiece()
{
  size_t n = rand() % shapes.size();
  switch (shapes[n]) {
  case 'I':
    return new Ipiece;
  case 'S':
    return new Spiece;
  default:
    cerr << "Error in PieceFactory::NewPiece()!!" << endl;
  }
  return NULL;
}
