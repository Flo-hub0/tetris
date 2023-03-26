/** \file Ipiece.h
    \brief Définit la classe pour représenter la pièce I du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _IPIECE_H
#define _IPIECE_H

#include <Piece.h>

using namespace std;

/** \brief Ipiece est la classe pour représenter la pièce I du jeu.
*/
class Ipiece : public Piece
{
public:
  /// \brief Construit la pièce I.
  Ipiece();
  /// \brief Constructeur par copie.
  Ipiece(Ipiece &other) : Piece(other) {};
  /// \brief Destructeur.
  virtual ~Ipiece() {};
  /// \brief Initialisation par assignation.
  Ipiece &operator=(Ipiece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape();

private:
  /// \brief Le centre de gravité de la pièce.
  static constexpr int center_of_gravity = 2;
  /// \brief Les positions occupées par la forme.
  static constexpr Position positions[] = { {0,0,0}, {0,1,0}, {0,2,0}, {0,3,0} };
};

#endif
