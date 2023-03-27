/** \file Jpiece.h
    \brief Définit la classe pour représenter la pièce J du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _JPIECE_H
#define _JPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Jpiece est la classe pour représenter la pièce J du jeu.
*/
class Jpiece : public Piece
{
public:
  /// \brief Construit la pièce J.
  Jpiece();
  /// \brief Constructeur par copie.
  Jpiece(Jpiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Jpiece() {};
  /// \brief Initialisation par assignation.
  Jpiece &operator=(Jpiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 1;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {0,0,0}, {0,1,0}, {0,2,0}, {1,0,0} };
};

#endif
