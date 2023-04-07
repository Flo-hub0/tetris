Auteur Corentin P et Charles R,
Dans le cadre du projet d'IN204

Pour compiler et executer le programme il suffit de taper la commande suivante dans le terminal:

    g++ -o main main.cpp -lglut -lGL -lGLU && ./main

Pour simplement executer le programme il suffit de taper la commande suivante dans le terminal:

    ./main


Commandes :

    'z' et 's' : rotation autour de l'axe X
    
    'q' et 'd' : rotation autour de l'axe Z
    
    'a' et 'e' : rotation autour de l'axe y
    
    barre d'espace : faire descendre la pièce pas à pas (translation sur l'axe Y)
    
    'f' : faire descendre la pièce tout en bas
    
    fléches du haut et du bas : translation en Z
    
    fléches gauche et droite : translation en X
    
    'r' : relancer une partie
    
    'c' : modifier l'angle de vue de la camèra (2 positions possibles)
    
    escape : quitter le jeu
    
Règles : 

    Le score croit exponentiellement -> 1 plan d'un coup = 1 point, 2 plans =2 points, 3 plans =7 points, 4 plans =15 points
    
    si la prochaine pièce ne peux pas apparaitre (collision) le jeu est fini,
    
    
    
    
    
    
    
