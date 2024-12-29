#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Person
{
    string name;
    string status;
    int ticket_number;
    int status_priority;
};

int getStatusPriority(string status) 
{
    if (status == "SVIP") return 1;
    if (status == "VIP") return 2;
    return 3;  // NORMAL
}

void heapify(vector<Person>& arr, int n, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].status_priority > arr[largest].status_priority)
        largest = left;

    if (right < n && arr[right].status_priority > arr[largest].status_priority)
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(vector<Person>& arr)
{
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 1; i--) 
    {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    ifstream file("data.txt");  
    if (!file) 
    {
        cerr << "Unable to open file!" << endl;
        return 1;
    }

    vector<Person> arr;
    string first_name, last_name, status;
    int ticket_number;
    
    while (file >> first_name >> last_name >> status >> ticket_number)
        {
        Person p;
        p.name = first_name + " " + last_name;
        p.status = status;
        p.ticket_number = ticket_number;
        p.status_priority = getStatusPriority(status);
        arr.push_back(p);
            
        cout << "Read: " << p.name << " " << p.status << " " << p.ticket_number << endl;
    }

    file.close();

    heap_sort(arr);

    cout << "\nSorted list based on priority (SVIP > VIP > NORMAL):\n";
    for (const auto& person : arr) 
    {
        cout << person.name << " " << person.status << " " << person.ticket_number << endl;
    }

    return 0;
}
