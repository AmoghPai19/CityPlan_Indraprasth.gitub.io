#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class WaterConsumptionData
{
public:
    char household[1000][30];
    int water_consumed[1000];
    int global_count;


    WaterConsumptionData();

    void welcome();
    void load_from_file();
    void display_data();
};

WaterConsumptionData::WaterConsumptionData()
{
    global_count = 0;  
}

void WaterConsumptionData::welcome()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tWATER CONSUMPTION DATA\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void WaterConsumptionData::load_from_file()
{
    ifstream file("water.txt");

    if (!file)
    {
        cout << "Error: File Not Found\n";
        return;
    }


    while (file >> household[global_count] >> water_consumed[global_count])
    {

        cout << "Reading: " << household[global_count] << " " << water_consumed[global_count] << endl;


        if (global_count < 1000)
            global_count++;
        else
        {
            cout << "Maximum data limit reached.\n";
            break;
        }
    }

    file.close();
}

void WaterConsumptionData::display_data()
{

    cout << setw(30) << "Household" << setw(30) << "Water Consumed (liters/day)" << endl;
    cout << string(60, '-') << endl;


    for (int i = 0; i < global_count; i++)
    {
        cout << setw(30) << household[i]
             << setw(30) << water_consumed[i]
             << endl;
    }
}

int main()
{
    WaterConsumptionData engine;
    engine.welcome();

    engine.load_from_file();
    engine.display_data();

    return 0;
}
