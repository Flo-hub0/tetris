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
  case 'J':
    return new Jpiece;
  case 'L':
    return new Lpiece;
  case 'O':
    return new Opiece;
  case 'S':
    return new Spiece;
  case 'T':
    return new Tpiece;
  case 'Z':
    return new Zpiece;
  default:
    cerr << "Error in PieceFactory::NewPiece()!!" << endl;
  }
  return NULL;
}
