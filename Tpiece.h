/** \file Tpiece.h
    \brief Définit la classe pour représenter la pièce T du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _TPIECE_H
#define _TPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Tpiece est la classe pour représenter la pièce T du jeu.
*/
class Tpiece : public Piece
{
public:
  /// \brief Construit la pièce T.
  Tpiece();
  /// \brief Constructeur par copie.
  Tpiece(Tpiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Tpiece() {};
  /// \brief Initialisation par assignation.
  Tpiece &operator=(Tpiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 1;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {1,0,0}, {1,1,0}, {1,2,0}, {0,1,0} };
};

#endif
