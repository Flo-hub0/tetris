/** \file Opiece.h
    \brief Définit la classe pour représenter la pièce O du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _OPIECE_H
#define _OPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Opiece est la classe pour représenter la pièce O du jeu.
*/
class Opiece : public Piece
{
public:
  /// \brief Construit la pièce O.
  Opiece();
  /// \brief Constructeur par copie.
  Opiece(Opiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Opiece() {};
  /// \brief Initialisation par assignation.
  Opiece &operator=(Opiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 0;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {0,0,0}, {0,1,0}, {1,0,0}, {1,1,0} };
};

#endif
