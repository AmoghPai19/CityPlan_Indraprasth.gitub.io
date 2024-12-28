#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    string inputFilename = "people_data.txt";
    string outputFilename = "area_population_summary.txt";

    ifstream inputFile(inputFilename);
    if (!inputFile) {
        cerr << "Error: Could not open the input file!" << endl;
        return 1;
    }

    string areas[] = {
        "Rajpur", "Kailashnagar", "Brahmapur", "Suryapet", "Anandvihar",
        "Kumbhpur", "Vasantgarh", "Chandrapur", "Madhavpuri", "Shivnagar"
    };

    int areaCount[10] = {0};

    string name, area;

    /
    while (inputFile >> area >> name) {
        for (int i = 0; i < 10; i++) {

            if (area == areas[i]) {
                areaCount[i]++;
                break;
            }
        }
    }

    inputFile.close();


    ofstream outputFile(outputFilename);
    if (!outputFile) {
        cerr << "Error: Could not open the output file!" << endl;
        return 1;
    }


    for (int i = 0; i < 10; i++) {
        outputFile << areas[i] << " " << areaCount[i] << endl;
    }

    outputFile.close();

    cout << "Area population summary has been generated in " << outputFilename << endl;

    return 0;
}
