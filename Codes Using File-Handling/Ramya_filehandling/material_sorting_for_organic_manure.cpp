#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class organic_data
{
private:
    int quantity[150];        
    char material_name[150][30]; 
    int global_count;

public:
    organic_data();

    void welcome();
    void load_from_file();
    void display_data();

 
    void quick_sort(int low, int high);
    int partition(int low, int high);
    void swap(int i, int j);

    
    int get_global_count() const;
};


organic_data::organic_data()
{
    global_count = 0;
}


void organic_data::welcome()
{
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tORGANIC MATERIALS DATA\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}


void organic_data::load_from_file()
{
    ifstream file("organic_materials.txt");  

    if (!file)
    {
        cout << "File Not Found\n";
        return;
    }

    int count;
    file >> count;  
    file.ignore();  
    cout << "Expected count: " << count << endl;  

    while (file >> quantity[global_count])
    {
        file.getline(material_name[global_count], 30);  
        cout << "Loaded: " << quantity[global_count] << " " << material_name[global_count] << endl; 
        global_count++;

        if (global_count >= count)  
        {
            break;
        }
    }

    file.close();
}


void organic_data::display_data()
{
    cout << setw(15) << "Quantity" << setw(30) << "Organic Material Name" << endl;
    for (int i = 0; i < global_count; i++)
    {
        cout << setw(15) << quantity[i] << setw(30) << material_name[i] << endl;
    }
}

void organic_data::quick_sort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);  

      
        quick_sort(low, pi - 1);
        quick_sort(pi + 1, high);
    }
}


int organic_data::partition(int low, int high)
{
    int pivot = quantity[high];  
    int i = (low - 1);  


    for (int j = low; j < high; j++)
    {
        if (quantity[j] < pivot)  
        {
            i++;
            swap(i, j);  
        }
    }
    swap(i + 1, high);  
    return (i + 1);
}


void organic_data::swap(int i, int j)
{
 
    int temp_qty = quantity[i];
    quantity[i] = quantity[j];
    quantity[j] = temp_qty;

   
    char temp_name[30];
    strcpy(temp_name, material_name[i]);
    strcpy(material_name[i], material_name[j]);
    strcpy(material_name[j], temp_name);
}


int organic_data::get_global_count() const
{
    return global_count;
}

int main()
{
    organic_data engine;
    engine.welcome();  

    engine.load_from_file(); 

    if (engine.get_global_count() > 0) {
        engine.quick_sort(0, engine.get_global_count() - 1);
        engine.display_data();    
    } else {
        cout << "No data to display." << endl;
    }

    return 0;
}
