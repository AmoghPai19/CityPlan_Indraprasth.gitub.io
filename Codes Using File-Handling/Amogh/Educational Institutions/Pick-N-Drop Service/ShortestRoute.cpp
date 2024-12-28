#include <iostream>
#include <fstream>
#include <string>
#include <limits.h>  // For INT_MAX
#define MAX 100

using namespace std;

class FloydWarshall {
public:
    int n;
    int D[MAX][MAX];
    string areas[MAX];

    FloydWarshall(int vertices);
    void readAreaData(string filename);
    void readDistanceData(string filename);
    void display();
    void shortestPath();
    void displayShortestPath();
};

FloydWarshall::FloydWarshall(int vertices) {
    n = vertices;
    // Initialize the distance matrix with infinity and 0 on diagonal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                D[i][j] = 0;  // Distance to itself is 0
            } else {
                D[i][j] = INT_MAX;  // Set to infinity
            }
        }
    }
}

void FloydWarshall::readAreaData(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open the area data file!" << endl;
        return;
    }

    int i = 0;  // Start from 0 since we initialized the matrix with n elements
    string area;
    int population;

    while (inputFile >> area >> population) {
        areas[i] = area;
        i++;
    }

    inputFile.close();
}

void FloydWarshall::readDistanceData(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Could not open the distance data file!" << endl;
        return;
    }

    // Read the distances between areas
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> D[i][j];  // Read the distances between areas
        }
    }

    inputFile.close();
}

void FloydWarshall::display() {
    cout << "The cost matrix is:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (D[i][j] == INT_MAX) {
                cout << "INF\t";  // If the distance is "infinity", display INF
            } else {
                cout << D[i][j] << "\t";  // Otherwise, display the distance
            }
        }
        cout << endl;
    }
}

void FloydWarshall::shortestPath() {
    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (D[i][k] != INT_MAX && D[k][j] != INT_MAX && (D[i][k] + D[k][j] < D[i][j])) {
                    D[i][j] = D[i][k] + D[k][j];  // Update the shortest distance
                }
            }
        }
    }
}

void FloydWarshall::displayShortestPath() {
    cout << "All pair shortest path matrix:" << endl;
    display();
}

int main() {
    int vertices;
    string areaDataFile = "area_population_data.txt";  // File containing areas and populations
    string distanceDataFile = "area_distances.txt";    // File containing distances between areas

    cout << "Enter the number of vertices (areas):" << endl;
    cin >> vertices;

    FloydWarshall graph(vertices);
    graph.readAreaData(areaDataFile);  // Read area and population data
    graph.readDistanceData(distanceDataFile);  // Read distance data

    graph.display();
    graph.shortestPath();
    graph.displayShortestPath();

    return 0;
}
