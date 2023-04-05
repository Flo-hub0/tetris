#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>

struct TetrisPiece
{
    int x, y, z;
    int type; // on ne s'en sert pas en vrai
    float colorR, colorG, colorB;
    std::vector<std::vector<int>> matrix;
    int rotationX, rotationZ;
};
// fonction qui calcule une piece si elle descendait tout en bas

std::vector<TetrisPiece> pieces;

std::vector<int> sacPiece = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
std::vector<int> sacCouleur = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};

std::vector<int> decalageScore = {-3, -12, -14};

std::vector<std::vector<int>> genererChiffre(int chiffre)
{
    std::vector<std::vector<int>> listePoints;

    switch (chiffre)
    {
    case 0:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {-1, 0, -1}, {4, 0, -1}, {-1, 1, -1}, {4, 1, -1}, {-1, 2, -1}, {4, 2, -1}, {-1, 3, -1}, {4, 3, -1}, {-1, 4, -1}, {0, 4, -1}, {1, 4, -1}, {2, 4, -1}, {3, 4, -1}, {4, 4, -1}};
        break;
    case 1:
        listePoints = {{1, -1, -1}, {2, -1, -1}, {2, 0, -1}, {2, 1, -1}, {1, 2, -1}, {2, 2, -1}, {3, 2, -1}, {4, 2, -1}};
        break;
    case 2:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {4, 0, -1}, {-1, 1, -1}, {4, 1, -1}, {-1, 2, -1}, {3, 2, -1}, {-1, 3, -1}, {2, 3, -1}, {-1, 4, -1}, {1, 4, -1}, {0, 4, -1}};
        break;
    case 3:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {4, 0, -1}, {-1, 1, -1}, {4, 1, -1}, {4, 2, -1}, {-1, 3, -1}, {4, 3, -1}, {-1, 4, -1}, {0, 4, -1}, {1, 4, -1}, {2, 4, -1}, {3, 4, -1}};
        break;
    case 4:
        listePoints = {{4, -1, -1}, {3, 0, -1}, {2, 1, -1}, {1, 2, -1}, {2, 2, -1}, {3, 2, -1}, {4, 2, -1}, {2, 3, -1}, {2, 4, -1}};
        break;
    case 5:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {-1, 0, -1}, {-1, 1, -1}, {4, 1, -1}, {4, 2, -1}, {-1, 3, -1}, {4, 3, -1}, {-1, 4, -1}, {0, 4, -1}, {1, 4, -1}, {2, 4, -1}, {3, 4, -1}, {4, 4, -1}};
        break;
    case 6:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {-1, 0, -1}, {-1, 1, -1}, {4, 1, -1}, {-1, 2, -1}, {4, 2, -1}, {-1, 3, -1}, {4, 3, -1}, {-1, 4, -1}, {0, 4, -1}, {1, 4, -1}, {2, 4, -1}, {3, 4, -1}, {4, 4, -1}};
        break;
    case 7:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {4, 0, -1}, {3, 1, -1}, {2, 2, -1}, {1, 3, -1}, {0, 4, -1}};
        break;
    case 8:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {-1, 0, -1}, {4, 0, -1}, {-1, 1, -1}, {4, 1, -1}, {-1, 2, -1}, {4, 2, -1}, {-1, 3, -1}, {4, 3, -1}, {-1, 4, -1}, {0, 4, -1}, {1, 4, -1}, {2, 4, -1}, {3, 4, -1}, {4, 4, -1}, {0, 2, -1}, {1, 2, -1}, {2, 2, -1}, {3, 2, -1}};
        break;
    case 9:
        listePoints = {{-1, -1, -1}, {0, -1, -1}, {1, -1, -1}, {2, -1, -1}, {3, -1, -1}, {4, -1, -1}, {-1, 0, -1}, {0, 0, -1}, {1, 0, -1}, {2, 0, -1}, {3, 0, -1}, {4, 0, -1}, {4, 1, -1}, {-1, 2, -1}, {4, 2, -1}, {-1, 3, -1}, {4, 3, -1}, {-1, 4, -1}, {0, 4, -1}, {1, 4, -1}, {2, 4, -1}, {3, 4, -1}, {4, 4, -1}};
        break;
    default:
        std::cout << "Chiffre invalide" << std::endl;
        break;
    }
    return listePoints;
}
int Score = 0;
double distance(std::vector<int> a, std::vector<int> b)
{
    double dist = 0;
    for (int i = 0; i < a.size(); i++)
    {
        dist += pow(a[i] - b[i], 2);
    }
    return sqrt(dist);
}

std::vector<std::vector<std::vector<int>>> separerPiece(std::vector<std::vector<int>> points)
{
    std::vector<std::vector<std::vector<int>>> groups;
    std::vector<bool> visited(points.size(), false);
    for (int i = 0; i < points.size(); i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            std::vector<std::vector<int>> group;
            group.push_back(points[i]);
            for (int j = i + 1; j < points.size(); j++)
            {
                if (!visited[j] && distance(points[i], points[j]) <= 1)
                {
                    visited[j] = true;
                    group.push_back(points[j]);
                }
            }
            groups.push_back(group);
        }
    }
    return groups;
}
// dimensions du terrain de jeu
int terrainDim[3][2] = {{-2, 3}, {-5, 6}, {-2, 2}};
int *calculePositionPiece(TetrisPiece piece, int point)
{
    int *position = new int[3];
    int cosX = cos(piece.rotationX * M_PI / 180);
    int sinX = sin(piece.rotationX * M_PI / 180);
    int cosZ = cos(piece.rotationZ * M_PI / 180);
    int sinZ = sin(piece.rotationZ * M_PI / 180);

    // std ::cout << piece.rotationX << " " << piece.rotationZ << std::endl;
    position[0] = piece.x + piece.matrix[point][0] * cosZ - piece.matrix[point][1] * sinZ;
    position[1] = piece.y + piece.matrix[point][0] * sinZ * cosX + piece.matrix[point][1] * cosX * cosZ - piece.matrix[point][2] * sinX;
    position[2] = piece.z + piece.matrix[point][0] * sinX * sinZ + piece.matrix[point][1] * sinX * cosZ + piece.matrix[point][2] * cosX;
    // std::cout << position[0] << " " << position[1] << " " << position[2] << std::endl;
    return position;
}

bool testCollision(std::vector<TetrisPiece> pieces)
{

    for (const auto &piece : pieces)
    {
        for (const auto &point : piece.matrix)
        {
            int *position = calculePositionPiece(piece, &point - &piece.matrix[0]);
            if (position[0] < terrainDim[0][0] || position[0] > terrainDim[0][1] || position[1] < terrainDim[1][0] || position[1] > terrainDim[1][1] || position[2] < terrainDim[2][0] || position[2] > terrainDim[2][1])
            {
                return true;
            }
        }
    }
    for (int i = 0; i < pieces.size(); i++)
    {
        for (int j = 0; j < pieces.size(); j++)
        {
            if (i != j)
            {
                for (const auto &point : pieces[i].matrix)
                {
                    for (const auto &point2 : pieces[j].matrix)
                    {
                        int *position = calculePositionPiece(pieces[i], &point - &pieces[i].matrix[0]);

                        int *position2 = calculePositionPiece(pieces[j], &point2 - &pieces[j].matrix[0]);

                        if (position[0] == position2[0] && position[1] == position2[1] && position[2] == position2[2])
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int32_t testPlanTermine(std::vector<TetrisPiece> &pieces)
{
    int nbligne = 0;
    int terrain[terrainDim[0][1] - terrainDim[0][0] + 1][terrainDim[1][1] - terrainDim[1][0] + 1][terrainDim[2][1] - terrainDim[2][0] + 1];
    for (int i = 0; i < terrainDim[0][1] - terrainDim[0][0] + 1; i++)
    {
        for (int j = 0; j < terrainDim[1][1] - terrainDim[1][0] + 1; j++)
        {
            for (int k = 0; k < terrainDim[2][1] - terrainDim[2][0] + 1; k++)
            {
                terrain[i][j][k] = 0;
            }
        }
    }
    for (const auto &piece : pieces)
    {
        for (const auto &point : piece.matrix)
        {
            int *position = calculePositionPiece(piece, &point - &piece.matrix[0]);
            terrain[position[0] - terrainDim[0][0]][position[1] - terrainDim[1][0]][position[2] - terrainDim[2][0]] = 1;
        }
    }
    for (int j = 0; j < terrainDim[1][1] - terrainDim[1][0] + 1; j++)
    {
        bool planTermine = true;
        for (int i = 0; i < terrainDim[0][1] - terrainDim[0][0] + 1; i++)
        {
            for (int k = 0; k < terrainDim[2][1] - terrainDim[2][0] + 1; k++)
            {
                if (terrain[i][j][k] == 0)
                {
                    planTermine = false;
                }
            }
        }
        if (planTermine)
        {
            nbligne++;
            for (int i = 0; i < pieces.size(); i++)
            {
                bool pieceSupprimee = false;
                for (int k = 0; k < pieces[i].matrix.size(); k++)
                {
                    int *position = calculePositionPiece(pieces[i], k);
                    if (position[1] == j + terrainDim[1][0])
                    {
                        pieces[i].matrix.erase(pieces[i].matrix.begin() + k);
                        pieceSupprimee = true;
                        k--;
                    }
                }
                if (pieceSupprimee)
                {
                    std::vector<std::vector<std::vector<int>>> groups = separerPiece(pieces[i].matrix);
                    if (groups.size() == 0)
                    {
                        pieces.erase(pieces.begin() + i);
                        i--;
                    }
                    if (groups.size() > 1)
                    {
                        pieces[i].matrix = groups[0];
                        for (int k = 1; k < groups.size(); k++)
                        {
                            TetrisPiece newPiece = pieces[i];
                            newPiece.matrix = groups[k];
                            pieces.push_back(newPiece);
                        }
                    }
                }
            }
            // à suprr
            if (testCollision(pieces))
            {

                std::cout << "error" << std::endl;
            }

            for (int i = 0; i < pieces.size(); i++)
            {
                pieces[i].y--;
                if (testCollision(pieces))
                {
                    pieces[i].y++;
                }
            }

            for (int i = 0; i < pieces.size(); i++)
            {
                if (pieces[i].matrix.size() == 0)
                {
                    pieces.erase(pieces.begin() + i);
                    i--;
                }
            }
            return 1 + testPlanTermine(pieces);
        }
    }
    return 0;
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    srand(time(0));
}

void createNewPiece(std::vector<TetrisPiece> &pieces)
{
    TetrisPiece newPiece;
    newPiece.x = 0;
    newPiece.y = 0;
    newPiece.z = 0;
    if (sacPiece.size() == 0)
    {
        sacPiece = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
        sacCouleur = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
    }

    int h = rand() % sacPiece.size();
    newPiece.type = sacPiece[h];
    sacPiece.erase(sacPiece.begin() + h);
    h = rand() % sacCouleur.size();
    int color = sacCouleur[h];
    sacCouleur.erase(sacCouleur.begin() + h);

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
    newPiece.rotationX = 0.0;
    newPiece.rotationZ = 0.0;

    switch (newPiece.type)
    {
    case 0: // I
        newPiece.matrix = {
            {0, 0, -1},
            {0, 0, 0},
            {0, 0, 1},
            {0, 0, 2}};
        break;
    case 1: // O
        newPiece.matrix = {
            {0, 0, 0},
            {0, 0, 1},
            {1, 0, 0},
            {1, 0, 1}};
        break;
    case 2: // T
        newPiece.matrix = {
            {0, 0, 0},
            {0, 0, 1},
            {-1, 0, 0},
            {1, 0, 0}};
        break;
    case 3: // S
        newPiece.matrix = {
            {0, 0, 0},
            {0, 0, 1},
            {1, 0, 1},
            {-1, 0, 0}};
        break;
    case 4: // Z
        newPiece.matrix = {
            {0, 0, 0},
            {-1, 0, 1},
            {0, 0, 1},
            {1, 0, 0}};
        break;
    case 5: // J
        newPiece.matrix = {
            {0, 0, 0},
            {-1, 0, 0},
            {-1, 0, -1},
            {1, 0, 0}};
        break;
    case 6: // L
        newPiece.matrix = {
            {0, 0, 0},
            {-1, 0, 0},
            {1, 0, 0},
            {1, 0, -1}};
        break;
    }

    pieces.push_back(newPiece);
    if (testCollision(pieces))
    {
        std::cout << "game over" << std::endl; // impossible de faire spawn en respectant les collisions => FINB DE PARTIE
        pieces.erase(pieces.begin(), pieces.end() - 1);
        sacPiece = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
        sacPiece.erase(std::find(sacPiece.begin(), sacPiece.end(), newPiece.type));
        sacCouleur = {0, 1, 2, 3, 4, 5, 6, 0, 1, 2, 3, 4, 5, 6};
        sacCouleur.erase(std::find(sacCouleur.begin(), sacCouleur.end(), color));
    }
}

bool testCollision(std::vector<TetrisPiece> pieces, TetrisPiece lastPiece)
{
    for (const auto &piece : pieces)
    {
        for (const auto &point : piece.matrix)
        {
            int *position = calculePositionPiece(piece, &point - &piece.matrix[0]);
            for (const auto &point2 : lastPiece.matrix)
            {
                int *position2 = calculePositionPiece(lastPiece, &point2 - &lastPiece.matrix[0]);
                if (position[0] == position2[0] && position[1] == position2[1] && position[2] == position2[2])
                {
                    return true;
                }
            }
        }
    }
    // ou avec le bord du terrain
    for (const auto &point2 : lastPiece.matrix)
    {
        int *position2 = calculePositionPiece(lastPiece, &point2 - &lastPiece.matrix[0]);
        if (position2[0] < terrainDim[0][0] || position2[0] > terrainDim[0][1] || position2[1] < terrainDim[1][0] || position2[1] > terrainDim[1][1] || position2[2] < terrainDim[2][0] || position2[2] > terrainDim[2][1])
        {
            return true;
        }
    }
    return false;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(4, 10, 4, -2, -10, -2, 0, 1, 0);

    for (const auto &piece : pieces)
    {
        glColor3f(piece.colorR, piece.colorG, piece.colorB);
        for (const auto &point : piece.matrix)
        {
            int *position = calculePositionPiece(piece, &point - &piece.matrix[0]);
            glPushMatrix();
            glTranslatef(position[0], position[1], position[2]);
            glutSolidCube(1);
            glPopMatrix();
        }
        glColor3f(0.0, 0.0, 0.0); // pour le fil de fer autour des cubes
        for (const auto &point : piece.matrix)
        {
            int *position = calculePositionPiece(piece, &point - &piece.matrix[0]);
            glPushMatrix();
            glTranslatef(position[0], position[1], position[2]);
            glutWireCube(1.01);
            glPopMatrix();
        }
    }

    glColor3f(0.2, 0.2, 0.2); // sol
    for (int i = terrainDim[0][0]; i <= terrainDim[0][1]; i++)
    {
        for (int j = terrainDim[2][0]; j <= terrainDim[2][1]; j++)
        {
            glPushMatrix();
            glTranslatef(i, terrainDim[1][0] - 1, j);

            glutWireCube(1);
            glPopMatrix();
        }
    }
    glColor3f(0.6, 0.6, 0.6);
    if (!pieces.empty())
    {
        TetrisPiece &lastPiece = pieces.back();
        for (const auto &point : lastPiece.matrix)
        {

            int *position = calculePositionPiece(lastPiece, &point - &lastPiece.matrix[0]);
            glPushMatrix();
            glTranslatef(position[0], terrainDim[1][0] - 1, position[2]);
            glutSolidCube(0.98);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(position[0], position[1], terrainDim[2][0] - 1);
            glutSolidCube(0.98);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(terrainDim[0][0] - 1, position[1], position[2]);
            glutSolidCube(0.98);
            glPopMatrix();
        }
    }
    // piece fantome
    glColor3f(1, 1, 1);
    if (!pieces.empty())
    {
        TetrisPiece lastPiece = pieces.back();
        TetrisPiece saveLastPiece = lastPiece;
        pieces.pop_back();

        while (!testCollision(pieces, lastPiece))
        {
            lastPiece.y--;
        }
        lastPiece.y++;
        for (const auto &point : lastPiece.matrix)
        {
            int *position = calculePositionPiece(lastPiece, &point - &lastPiece.matrix[0]);
            glPushMatrix();
            glTranslatef(position[0], position[1] + 0.025, position[2]);
            glutWireCube(1.02);
            glPopMatrix();
        }
        pieces.push_back(saveLastPiece);
    }
    // afficher le score
    std::vector<std::vector<int>> score = genererChiffre(Score);
    for (const auto &point : score)
    {
        glPushMatrix();
        glTranslatef(point[0] + decalageScore[0], point[1] + decalageScore[1], point[2] + decalageScore[2]);
        glutSolidCube(1);
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
        createNewPiece(pieces);
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
                Score += testPlanTermine(pieces);
                createNewPiece(pieces);
            }
        }
        break;
    case 27: // ASCII code for escape
        exit(0);
        break;

    case 'r':
        pieces.erase(pieces.begin(), pieces.end());
        break;

    case 'f':
        if (pieces.empty())
        {
            return;
        }
        else
        {
            while (!testCollision(pieces))
            {
                lastPiece.y -= 1;
            }
            lastPiece.y += 1;
            Score += testPlanTermine(pieces);
            createNewPiece(pieces);
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
        lastPiece.z -= 1;
        if (testCollision(pieces))
        {
            lastPiece.z += 1;
        }
        break;
    case GLUT_KEY_DOWN:
        lastPiece.z += 1;
        if (testCollision(pieces))
        {
            lastPiece.z -= 1;
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
    gluPerspective(55, (float)w / h, 0.1, 100);
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