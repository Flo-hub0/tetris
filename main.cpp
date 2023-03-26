/** \file main.h
    \brief Programme qui lance le jeu de tetris.
    
    \date 25 mars 2023
    \author Florine Lefer - ENSTA
*/

#include <Ipiece.h>
#include <Spiece.h>
#include <PieceFactory.h>
#include <Field.h>

int
main(int argc, char *argv[])
{
  PieceFactory factory;
  
  Field field({6,10,1}, factory);

  cout << "Actions possibles :" << endl;
  cout << "  start : demarrer le jeu" << endl;
  cout << "  u (Update) : fait tomber la pièce d'un niveau" << endl;
  cout << "  l (Left) : déplace la pièce sur la gauche" << endl;
  cout << "  r (Right) : déplace la pièce sur la droite" << endl;
  cout << "  for (FORward) : déplace la pièce vers l'avant" << endl;
  cout << "  back (BACKward) : déplace la pièce vers l'arrière" << endl;
  cout << "  cw (rotate Clock Wise) : tourne la pièce dans le sens des aiguilles d'une montre" << endl;
  cout << "  ccw (rotate Counter Clock Wise) : tourne la pièce dans le sens contraire des aiguilles d'une montre" << endl;
  cout << "  rfor (Rotate FORward) : tourne la pièce vers l'avant (axe horizontal)" << endl;
  cout << "  rback (Rotate BACKward) : tourne la pièce vers l'arrière (axe horizontal)" << endl;
  cout << "  reset : réinitialiser le jeu" << endl << endl;
  while (!field.IsGameOver()) {
    field.Print();
    string action;
    cin >> action;
    if (action == "u") {
      field.Update();
    } else if (action == "l") {
      field.Left();
    } else if (action == "r") {
      field.Right();
    } else if (action == "for") {
      field.Forward();
    } else if (action == "back") {
      field.Backward();
    } else if (action == "cw") {
      field.RotateCW();
    } else if (action == "ccw") {
      field.RotateCCW();
    } else if (action == "rfor") {
      field.RotateForward();
    } else if (action == "rback") {
      field.RotateBackward();
    } else if (action == "start") {
      field.Start();
    } else if (action == "reset") {
      field.Reset();
    } else cerr << "Unknown command" << endl;
  }
  field.Print();
  cout << endl << "Game is over ! Your score is " << field.GetScore() << endl << endl;
  return 0;
}
