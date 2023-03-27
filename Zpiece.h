/** \file Zpiece.h
    \brief Définit la classe pour représenter la pièce Z du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _ZPIECE_H
#define _ZPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Zpiece est la classe pour représenter la pièce Z du jeu.
*/
class Zpiece : public Piece
{
public:
  /// \brief Construit la pièce Z.
  Zpiece();
  /// \brief Constructeur par copie.
  Zpiece(Zpiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Zpiece() {};
  /// \brief Initialisation par assignation.
  Zpiece &operator=(Zpiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 1;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {1,0,0}, {1,1,0}, {0,1,0}, {0,2,0} };
};

#endif
