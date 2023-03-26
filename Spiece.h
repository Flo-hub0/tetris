/** \file Spiece.h
    \brief Définit la classe pour représenter la pièce S du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _SPIECE_H
#define _SPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Spiece est la classe pour représenter la pièce S du jeu.
*/
class Spiece : public Piece
{
public:
  /// \brief Construit la pièce S.
  Spiece();
  /// \brief Constructeur par copie.
  Spiece(Spiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Spiece() {};
  /// \brief Initialisation par assignation.
  Spiece &operator=(Spiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 2;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {0,0,0}, {0,1,0}, {1,1,0}, {1,2,0} };
};

#endif
