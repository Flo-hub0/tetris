/** \file Piece.h
    \brief Définit une classe générique pour représenter une pièce du jeu.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _PIECE_H
#define _PIECE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/** \brief Une case du plateau de jeu.
*/
typedef struct {
  int x, y, z;
} Position;

/** \brief Piece est une classe générique pour représenter une pièce du jeu de tetris.

    Elle gère le déplacement et les rotations de la pièce indépendemmant de toute contrainte car n'ayant aucune connaissance de l'environnent.
    Les pièces sont des pièces 3D, en version 2D il suffira de ne pas autoriser les rotations autour de Oz (profondeur) au niveau de l'IHM.
    Par convention la dimension X sera toujours la dimension verticale, dirigée vers le haut, que l'on soit en 2D ou en 3D.
    Y est l'horizontale, dirigée vers la droite et Z la profondeur, dirigée vers l'arrière (repère direct).
*/
class Piece
{
public:
  /// \brief Construit une pièce.
  Piece();
  /// \brief Constructeur par copie.
  Piece(Piece &other);
  /// \brief Destructeur.
  virtual ~Piece();
  /// \brief Initialisation par assignation.
  Piece &operator=(Piece &other);
  /// \brief Renvoie le nom de la pièce.
  virtual string ShapeName() const;
  /// \brief Définit la géométrie de la pièce.
  virtual void SetShape() {};
  /// \brief Renvoie l'encombrement de la pièce.
  inline vector<vector<int> > Footprint() const {return this->footprint;};
  /// \brief Renvoie les positions occupées par la pièce.
  inline vector<Position> Positions() const {return this->shape;};
  /// \brief Positionne la pièce en haut au centre du jeu.
  /// \param dimensions contient les dimensions du plateau.
  void SetTopCenter(vector<int> dimensions);
  /// \brief Fait tomber la pièce d'un niveau.
  void Down();
  /// \brief Déplace la pièce d'une case vers la gauche.
  void Left();
  /// \brief Déplace la pièce d'une case vers la droite.
  void Right();
  /// \brief Déplace la pièce d'une case vers l'avant.
  void Forward();
  /// \brief Déplace la pièce d'une case vers l'arrière.
  void Backward();
  /// \brief Fait tourner la pièce dans le plan de l'écran d'un quart de tour dans le sens des aiguilles d'une montre.
  void RotateCW();
  /// \brief Fait tourner la pièce dans le plan de l'écran d'un quart de tour dans le sens contraire des aiguilles d'une montre.
  void RotateCCW();
  /// \brief Fait tourner la pièce autour de Ox d'un quart de tour vers l'avant.
  void RotateForward();
  /// \brief Fait tourner la pièce autour de Ox d'un quart de tour vers l'arrière.
  void RotateBackward();
  /// \brief Annule la dernière transformation géométrique appliquée à la pièce.
  /// Cette fonctionalité est utile pour le plateau, qui va appliquer une transformation, tester sa validité et éventuellement l'annuler si celle-ci n'est pas valide.
  void Undo();
  
protected:
  /// \brief Le centre de gravité de la pièce, i.e. par rapport auquel seront effectuées les rotations, donnée par son indice dans la liste de ses positions.
  size_t gravity;
  /// \brief Les positions occupées par la pièce.
  vector<Position> shape, old_shape;
  /// \brief L'encombrement de la pièce.
  /// L'encombrement est constitué des extrema, soit 2 ou 3 couples <min,max>.
  vector<vector<int> > footprint, old_footprint;
  /// \brief Calcule la boîte englobante de la pièce.
  void ComputeFootprint();

private:
  /// \brief Sauvegarde des paramètres afin de pouvoir défaire la prochaine transformations géométrique.
  /// Cette opération doit être appliquée au début de toute définition de transformation géométrique.
  void SaveForRestore();
};

/// \brief Imprime les paramètres de la pièce.
ostream &operator<<(ostream &os, const Piece &p);

#endif
