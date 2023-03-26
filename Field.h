/** \file Field.h
    \brief Définit le plateau de jeu de tetris.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#ifndef _FIELD_H
#define _FIELD_H

#include <iostream>
#include <sstream>
#include <string>
#include <PieceFactory.h>

using namespace std;

/** \brief Field est une classe pour représenter le plateau du jeu de tetris.

    Cette classe gère le mouvement de la pièce active sous environnement contraint.
    Par convention la dimension X sera toujours la dimension verticale, dirigée vers le haut, que l'on soit en 2D ou en 3D.
    Y est l'horizontale, dirigée vers la droite et Z la profondeur, dirigée vers l'arrière (repère direct).
    Le plateau reçoit les évènements de l'interface graphique et exécute les callbacks associés.
*/
class Field
{
public:
  /// \brief Construit un plateau.
  /// \param dimensions Les dimensions du plateau sous la forme xmin, xmax, ymin, etc,
  /// 4 ou 6 valeurs selon qu'on est en 2D ou 3D.
  /// \param factory L'usine à pièces, qui sera appelée lorsqu'une nouvelle pièce sera requise.
  Field(vector<int> dimensions, PieceFactory factory);
  /// \brief Constructeur par copie.
  Field(Field &other);
  /// \brief Destructeur.
  ~Field();
  /// \brief Initialisation par assignation.
  Field &operator=(Field &other);
  /// \brief Renvoie le nom de la classe.
  inline string getName() const {return "Field";};
  /// \brief Renvoie les dimensions du plateau.
  inline const vector<int> GetDimensions() const {return this->dimensions;};
  /// \brief Dimensionne le plateau.
  void SetDimensions(vector<int> dimensions);
  /// \brief Déplace la pièce active sur la gauche si le mouvement est possible.
  void Left();
  /// \brief Déplace la pièce active sur la droite si le mouvement est possible.
  void Right();
  /// \brief Déplace la pièce active vers l'avant si le mouvement est possible.
  void Forward();
  /// \brief Déplace la pièce active vers l'arrière si le mouvement est possible.
  void Backward();
  /// \brief Fait tourner la pièce active dans le plan de l'écran d'un quart de tour dans le sens des aiguilles d'une montre si le mouvement est possible.
  void RotateCW();
  /// \brief Fait tourner la pièce active dans le plan de l'écran d'un quart de tour dans le sens contraire des aiguilles d'une montre si le mouvement est possible.
  void RotateCCW();
  /// \brief Fait tourner la pièce active autour de Ox d'un quart de tour vers l'avant si le mouvement est possible.
  void RotateForward();
  /// \brief Fait tourner la pièce active autour de Ox d'un quart de tour vers l'arrière si le mouvement est possible.
  void RotateBackward();
  /// \brief Renvoie les positions occupées par la pièce active, utile pour l'affichage.
  inline const vector<Position> ActivePiecePositions() const {return this->active->Positions();};
  /// \brief Modifie le niveau actuel du jeu.
  void SetLevel(int level);
  /// \brief Renvoie le niveau actuel du jeu.
  inline int GetLevel() const {return this->level;};
  /// \brief Renvoie le score de l'utilisateur.
  inline int GetScore() const {return this->score;};
  /// \brief Renvoie vrai si le jeu est terminé.
  inline bool IsGameOver() const {return this->isover;};
  /// \brief Réinitialise le jeu à la situation de départ.
  void Reset();
  /// \brief Commence le jeu.
  void Start();
  /// \brief Met à jour la position de la pièce active en réponse à la force gravitationnelle.
  /// Si la position ne peut être mise à jour à cause de la présence d'une autre pièce en dessous, la pièce n'est plus active.
  /// La sémantique utilisée est que si la pièce atteint un niveau où elle ne peut descendre davantage, ce n'est que lors de l'itération suivante
  /// qu'elle sera figée, autrement après avoir tenté de descendre au niveau impossible.
  /// C'est en principe comme cela que le logiciel d'origine se comporte.
  void Update();
  
private:
  /// \brief Renvoie vrai si la position et l'orientation de la pièce active est valide, i.e. n'entre pas en collision avec des briques.
  bool CheckValidity() const;
  /// \brief Renvoie vrai si l'étage n est totalement rempli de briques.
  /// Un étage peut être une ligne en 2D ou un rectangle en 3D.
  bool IsFilled(int n) const;
  /// \brief Les dimensions du plateau.
  vector<int> dimensions;
  /// \brief La taille d'un niveau.
  /// On stocke cette valeur afin d'accélérer les calculs car elle sera souvent utlisée.
  int floor_size;
  /// \brief La grille pour gérer l'occupation de l'espace.
  /// True pour les cases occupées, false pour les cases libres.
  vector<bool> grid;
  /// \brief La pièce active, autrement dit la pièce gérée par le joueur.
  Piece *active;
  /// \brief L'usine à pièces, qui sera appelée lorsqu'une nouvelle pièce sera requise.
  PieceFactory factory;
  /// \brief Le niveau actuel du jeu.
  int level;
  /// \brief Le score de l'utilisateur.
  int score;
  /// \brief Le jeu est-il terminé ?
  bool isover;

public:
  // Cette methode n'est la que pour la phase de mise au point, afin de pouvoir visualiser le contenu de la grille
  void Print() const {
    for (int i=this->dimensions[0]-1 ; i>=0 ; i--) {
      for (int j=0 ; j<this->dimensions[1] ; j++) {
	if (this->active != NULL) {
	  Position p;
	  p.x = i; p.y = j; p.z = 0;
	  vector<Position> v = this->active->Positions();
	  size_t i;
	  for (i=0 ; i<v.size() ; i++)
	    if (p.x == v[i].x && p.y == v[i].y && p.z == v[i].z) {
	      cout << " o";
	      break;
	    }
	  if (i < v.size())
	    continue;
	}
	cout << (this->grid[i*this->floor_size+j] ? " x" : " -");
      }
      cout << endl;
    }
    if (this->active != NULL)
      cout << *this->active;
    cout << "Score : " << this->score << endl;
  }
};

/// \brief Imprime les paramètres du plateau.
ostream &operator<<(ostream &os, const Field &f);

#endif
