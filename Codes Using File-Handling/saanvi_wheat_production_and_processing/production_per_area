#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct AreaProduction {
    string area;
    int production;
};

int main() {
    ifstream inputFile("delhi_wheat_production.txt");

    if (!inputFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    AreaProduction areaProduction[50000];
    int count = 0;

    string area;
    int production;

    while (inputFile >> area >> production) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (areaProduction[i].area == area) {
                areaProduction[i].production += production;
                found = true;
                break;
            }
        }

        if (!found) {
            areaProduction[count].area = area;
            areaProduction[count].production = production;
            count++;
        }
    }

    inputFile.close();

    cout << "Production Totals by Area:" << endl;
    for (int i = 0; i < count; i++) {
        cout << areaProduction[i].area << ": " << areaProduction[i].production << endl;
    }

    return 0;
}
