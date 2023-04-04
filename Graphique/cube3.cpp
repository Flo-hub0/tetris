#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cstdlib>
#include <ctime>

// Structure pour décrire une pièce de Tetris
struct TetrisPiece {
    float x, y, z;
    int type;
    std::vector<std::vector<int>> matrix;
    float rotationX, rotationZ;
};

std::vector<TetrisPiece> pieces;

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    srand(time(0));
}

void createNewPiece() {
    TetrisPiece newPiece;
    newPiece.x = 0.0;
    newPiece.y = 0.0;
    newPiece.z = 0.0;
    //newPiece.type = rand() % 7;
    newPiece.type = 0;
    newPiece.rotationX = 0.0;
    newPiece.rotationZ = 0.0;

    switch (newPiece.type) {
        case 0: // J
            newPiece.matrix = { {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {1, 2, 0} };
            break;
        // Ajoutez les autres types de pièces ici
    }

    pieces.push_back(newPiece);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5, 10, 10, 0, 0, 0, 0, 1, 0);

    for (const auto& piece : pieces) {
        glPushMatrix();
        glTranslatef(piece.x, piece.y, piece.z);
        glRotatef(piece.rotationX, 1, 0, 0);
        glRotatef(piece.rotationZ, 0, 0, 1);

        for (const auto& coord : piece.matrix) {
            glPushMatrix();
            glTranslatef(coord[0], coord[1], coord[2]);
            glutSolidCube(1);
            glPopMatrix();
        }
        glPopMatrix();
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    TetrisPiece& lastPiece = pieces.back();

    switch (key) {
        case 'p':
            createNewPiece();
        break;
        case 'z':
            if (pieces.empty()) {return;}
            else{lastPiece.rotationX+=90;}
        break;
        case 's':
            if (pieces.empty()) {return;}
            else{lastPiece.rotationX-=90;}
        break;
        case 'q':
            if (pieces.empty()) {return;}
            else{lastPiece.rotationZ+=90;}
        break;
        case 'd':
            if (pieces.empty()) {return;}
            else{lastPiece.rotationZ-=90;}
        break;
        case 32:                            //ASCII code for spacebar
            if (pieces.empty()) {return;}
            else{lastPiece.y-=1;}
        break;

    }
// Ajouter ici les touches pour déplacer et faire pivoter les pièces
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
    if (pieces.empty()) {
        return;
    }

    TetrisPiece& lastPiece = pieces.back();

    switch (key) {
        case GLUT_KEY_UP:
            lastPiece.z += 1;
            break;
        case GLUT_KEY_DOWN:
            lastPiece.z -= 1;
            break;
        case GLUT_KEY_LEFT:
            lastPiece.x -= 1;
            break;
        case GLUT_KEY_RIGHT:
            lastPiece.x += 1;
            break; 
    }

    glutPostRedisplay();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tetris 3D");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
