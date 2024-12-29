#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <queue>  
using namespace std;


struct FoodEntry {
    string name;
    string dish;
    string location;
    int bill;
};

class food_data
{
private:
    queue<FoodEntry> foodQueue;  

public:
    food_data();

    void welcome();
    void load_from_file();
    void display_data();
};

food_data::food_data() {}

void food_data::welcome()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tFOOD LIST\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void food_data::load_from_file()
{
    ifstream file("food.txt");

    if (!file)
    {
        cout << "File Not Found\n";
        return;
    }

    cout << "Reading file...\n";
    string line;

    while (getline(file, line))
    {
        stringstream ss(line); 
        string temp;

        FoodEntry entry;

        
        getline(ss, temp, ',');
        entry.name = temp.substr(temp.find(":") + 2); 

        
        getline(ss, temp, ',');
        entry.dish = temp.substr(temp.find(":") + 2); 

       
        getline(ss, temp, ',');
        entry.location = temp.substr(temp.find(":") + 2); 

        
        getline(ss, temp); 
        entry.bill = stoi(temp.substr(temp.find(":") + 2)); 

        
        foodQueue.push(entry);

       
        cout << "Loaded: " << entry.name << ", "
             << entry.dish << ", "
             << entry.location << ", "
             << entry.bill << endl;
    }

    if (foodQueue.empty())
    {
        cout << "No data loaded. Please check your file format.\n";
    }

    file.close();
}

void food_data::display_data()
{
    cout << setw(30) << "Name"
         << setw(30) << "Dish"
         << setw(30) << "Location"
         << setw(10) << "Bill" << endl;
    cout << "---------------------------------------------------------------" << endl;

    while (!foodQueue.empty())
    {
        FoodEntry entry = foodQueue.front();  
        foodQueue.pop();  

        cout << setw(30) << entry.name
             << setw(30) << entry.dish
             << setw(30) << entry.location
             << setw(10) << entry.bill << endl;
    }
}

int main()
{
    food_data list;
    list.welcome();

    list.load_from_file();
    list.display_data();

    return 0;
}

