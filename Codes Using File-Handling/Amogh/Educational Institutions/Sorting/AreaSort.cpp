#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Area {
    string name;
    int population;
};

int Partition(Area A[], int l, int r) {
    int pivot = A[l].population;
    int i = l;
    int j = r + 1;

    while (true) {
        do {
            i++;
        } while (i <= r && A[i].population <= pivot);

        do {
            j--;
        } while (A[j].population > pivot);

        if (i >= j)
            break;

        swap(A[i], A[j]);
    }

    swap(A[l], A[j]);

    return j;
}

void QuickSort(Area A[], int l, int r) {
    if (l < r) {
        int s = Partition(A, l, r);
        QuickSort(A, l, s - 1);
        QuickSort(A, s + 1, r);
    }
}

int main() {
    string filename = "population_data.txt";

    ifstream inputFile(filename);

    if (!inputFile) {
        cerr << "Error: Could not open the file!" << endl;
        return 1;
    }

    int numAreas = 0;
    string areaName;
    int population;

    while (inputFile >> areaName >> population) {
        numAreas++;
    }

    inputFile.close();

    Area* areas = new Area[numAreas];

    inputFile.open(filename);

    int index = 0;
    while (inputFile >> areaName >> population) {
        areas[index].name = areaName;
        areas[index].population = population;
        index++;
    }

    inputFile.close();

    QuickSort(areas, 0, numAreas - 1);

    cout << "Areas sorted by population (highest to lowest):" << endl;
    for (int i = 0; i < numAreas; i++) {
        cout << "Area: " << areas[i].name << ", Population: " << areas[i].population << endl;
    }

    delete[] areas;

    return 0;
}
