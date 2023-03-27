/** \file Lpiece.h
    \brief Définit la classe pour représenter la pièce L du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _LPIECE_H
#define _LPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Lpiece est la classe pour représenter la pièce L du jeu.
*/
class Lpiece : public Piece
{
public:
  /// \brief Construit la pièce L.
  Lpiece();
  /// \brief Constructeur par copie.
  Lpiece(Lpiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Lpiece() {};
  /// \brief Initialisation par assignation.
  Lpiece &operator=(Lpiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 2;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {0,0,0}, {1,0,0}, {1,1,0}, {1,2,0} };
};

#endif
