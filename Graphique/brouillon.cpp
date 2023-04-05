
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>

std::vector<std::vector<int>> matrix;

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

void printMatrix(std::vector<std::vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[0].size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void printMatrix(std::vector<std::vector<std::vector<int>>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        std::cout << "Group " << i << std::endl;
        printMatrix(matrix[i]);
        std::cout << std::endl;
    }
}
int main()
{
    srand(time(NULL));

    matrix = {{0, 0, 0}, {1, 0, 0}, {0, 0, 1}, {-2, 0, 1}, {-2, 0, 0}};
    printMatrix(matrix);
    std::cout << std::endl;
    std::cout << "Neighbours" << std::endl;
    std::vector<std::vector<std::vector<int>>> neighbours = separerPiece(matrix);
    printMatrix(neighbours);

    return 0;
}