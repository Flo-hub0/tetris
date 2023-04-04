#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

// Structure pour décrire une pièce de Tetris
struct TetrisPiece
{
    float x, y, z;
    int type; // on ne s'en sert pas en vrai
    float colorR, colorG, colorB;
    std::vector<std::vector<int>> matrix;
    float rotationX, rotationZ;
};

std::vector<TetrisPiece> pieces;

bool testCollision(std::vector<TetrisPiece> pieces)
{

    for (const auto &piece : pieces)
    {
        // tester qu'aucune case de la pièce ne dépasse des limites du tableau ou si il touche le fond
        for (const auto &point : piece.matrix)
        {
            if (point[0] + piece.x < -5 || point[0] + piece.x >= 5 || point[1] + piece.y < -5 || point[1] + piece.y >= 5 || point[2] + piece.z < -5 || point[2] + piece.z >= 5)
            {
                std::cout << "collision" << point[0] + piece.x << " " << point[1] + piece.y << " " << point[2] + piece.z << std::endl;
                return true;
            }
        }
    }
    // tester qu'aucune case de la pièce ne soit déjà occupée par une autre pièce, en prenant compte de la position x,y,z de la pièce sans comparer une pièce avec elle-même
    for (int i = 0; i < pieces.size() - 1; i++)
    {
        for (int j = i + 1; j < pieces.size(); j++)
        {
            for (const auto &point : pieces[i].matrix)
            {
                for (const auto &point2 : pieces[j].matrix)
                {
                    if (point[0] + pieces[i].x == point2[0] + pieces[j].x && point[1] + pieces[i].y == point2[1] + pieces[j].y && point[2] + pieces[i].z == point2[2] + pieces[j].z)
                    {
                        std::cout << "collision entre piece " << point[0] + pieces[i].x << " " << point[1] + pieces[i].y << " " << point[2] + pieces[i].z << std::endl;
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    srand(time(0));
}

void createNewPiece()
{
    TetrisPiece newPiece;
    newPiece.x = 0.0;
    newPiece.y = 0.0;
    newPiece.z = 0.0;
    newPiece.type = rand() % 7;
    int color = rand() % 7;
    switch (color)
    {
    case 0:
        newPiece.colorR = 1.0;
        newPiece.colorG = 0.0;
        newPiece.colorB = 0.0;
        break;
    case 1:
        newPiece.colorR = 0.0;
        newPiece.colorG = 1.0;
        newPiece.colorB = 0.0;
        break;
    case 2:
        newPiece.colorR = 0.0;
        newPiece.colorG = 0.0;
        newPiece.colorB = 1.0;
        break;
    case 3:
        newPiece.colorR = 1.0;
        newPiece.colorG = 1.0;
        newPiece.colorB = 0.0;
        break;
    case 4:
        newPiece.colorR = 1.0;
        newPiece.colorG = 0.0;
        newPiece.colorB = 1.0;
        break;
    case 5:
        newPiece.colorR = 0.0;
        newPiece.colorG = 1.0;
        newPiece.colorB = 1.0;
        break;
    case 6:
        newPiece.colorR = 1.0;
        newPiece.colorG = 1.0;
        newPiece.colorB = 1.0;
        break;
    }
    std::cout << newPiece.type << std::endl;
    newPiece.type = 0;
    newPiece.rotationX = 0.0;
    newPiece.rotationZ = 0.0;

    switch (newPiece.type)
    {
    case 0: // J
        newPiece.matrix = {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {1, 2, 0}};
        break;
    case 1: // L
        newPiece.matrix = {{0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {1, 2, 0}};
        break;
    case 2: // O
        newPiece.matrix = {{0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {1, 1, 0}};
        break;
    case 3: // S
        newPiece.matrix = {{0, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 2, 0}};
        break;
    case 4: // T
        newPiece.matrix = {{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {2, 0, 0}};
        break;
    case 5: // Z
        newPiece.matrix = {{0, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 2, 0}};
        break;
    case 6: // I
        newPiece.matrix = {{0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {0, 3, 0}};
        break;
    }

    pieces.push_back(newPiece);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5, 10, 10, 0, 0, 0, 0, 1, 0);
    if (pieces.size() > 0)
    {
        std::cout << pieces[pieces.size() - 1].type << std::endl;
    }

    for (const auto &piece : pieces)
    {
        glPushMatrix();
        glTranslatef(piece.x, piece.y, piece.z);
        glRotatef(piece.rotationX, 1, 0, 0);
        glRotatef(piece.rotationZ, 0, 0, 1);

        for (const auto &coord : piece.matrix)
        {
            glPushMatrix();
            glTranslatef(coord[0], coord[1], coord[2]);
            glutSolidCube(1);
            glColor3f(piece.colorR, piece.colorG, piece.colorB);

            glPopMatrix();
        }
        glPopMatrix();
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
    TetrisPiece &lastPiece = pieces.back();

    switch (key)
    {
    case 'p':
        createNewPiece();
        break;
    case 'z':
        if (pieces.empty())
        {
            return;
        }
        else
        {
            lastPiece.rotationX += 90;
            if (testCollision(pieces))
            {
                lastPiece.rotationX -= 90;
            }
        }
        break;
    case 's':
        if (pieces.empty())
        {
            return;
        }
        else
        {
            lastPiece.rotationX -= 90;
            if (testCollision(pieces))
            {
                lastPiece.rotationX += 90;
            }
        }
        break;
    case 'q':
        if (pieces.empty())
        {
            return;
        }
        else
        {
            lastPiece.rotationZ += 90;
            if (testCollision(pieces))
            {
                lastPiece.rotationZ -= 90;
            }
        }
        break;
    case 'd':
        if (pieces.empty())
        {
            return;
        }
        else
        {
            lastPiece.rotationZ -= 90;
            if (testCollision(pieces))
            {
                lastPiece.rotationZ += 90;
            }
        }
        break;
    case 32: // ASCII code for spacebar
        if (pieces.empty())
        {
            return;
        }
        else
        {
            lastPiece.y -= 1;
            if (testCollision(pieces))
            {
                lastPiece.y += 1;
                createNewPiece();
            }
        }
        break;
    }

    // Ajouter ici les touches pour déplacer et faire pivoter les pièces
    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
    if (pieces.empty())
    {
        return;
    }

    TetrisPiece &lastPiece = pieces.back();

    switch (key)
    {
    case GLUT_KEY_UP:
        lastPiece.z += 1;
        if (testCollision(pieces))
        {
            lastPiece.z -= 1;
        }
        break;
    case GLUT_KEY_DOWN:
        lastPiece.z -= 1;
        if (testCollision(pieces))
        {
            lastPiece.z += 1;
        }
        break;
    case GLUT_KEY_LEFT:
        lastPiece.x -= 1;
        if (testCollision(pieces))
        {
            lastPiece.x += 1;
        }
        break;
    case GLUT_KEY_RIGHT:
        lastPiece.x += 1;
        if (testCollision(pieces))
        {
            lastPiece.x -= 1;
        }
        break;
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w / h, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
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