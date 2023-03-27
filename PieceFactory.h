/** \file PieceFactory.h
    \brief Définit une usine à pièces pour le jeu de tetris.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _PIECE_FACTORY_H
#define _PIECE_FACTORY_H

#include <Ipiece.h>
#include <Jpiece.h>
#include <Lpiece.h>
#include <Opiece.h>
#include <Spiece.h>
#include <Tpiece.h>
#include <Zpiece.h>
#include <array>

/// \brief La liste des types de pièce générées par l'usine.
static constexpr array<char, 7> shapes { 'I', 'J', 'L', 'O', 'S', 'T', 'Z' };

using namespace std;

/** \brief PieceFactory est une usine à pièces pour le jeu de tetris.

    Cette classe a pour mission de fournir des pièces à la demande, la forme de la pièce étant aléatoire.
*/
class PieceFactory
{
public:
  /// \brief Construit une usine à pièces.
  PieceFactory();
  /// \brief Constructeur par copie.
  PieceFactory(PieceFactory &other) {};
  /// \brief Destructeur.
  ~PieceFactory() {};
  /// \brief Initialisation par assignation.
  PieceFactory &operator=(PieceFactory &other) {return *this;};
  /// \brief Renvoie le nom de la classe.
  inline string ClassName() const {return "PieceFactory";};
  /// \brief Fabrique une nouvelle pièce.
  Piece *NewPiece();
};

#endif
