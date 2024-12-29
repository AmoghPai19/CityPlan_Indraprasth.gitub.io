#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

class ticket_data {
private:
    char name[150][30];
    char ticket_number[150][15];
    char purchase_date[150][15];
    int global_count;

    // Function to partition the array for QuickSort based on ticket_number
    int Partition(int l, int r) {
        string pivot = ticket_number[l];
        int i = l + 1; // Start from the next element
        int j = r;

        while (true) {
            // Move i to the right while elements are less than or equal to the pivot
            while (i <= r && string(ticket_number[i]) <= pivot) {
                i++;
            }

            // Move j to the left while elements are greater than the pivot
            while (j >= l && string(ticket_number[j]) > pivot) {
                j--;
            }

            if (i >= j)
                break;

            // Swap the elements in ticket_number array
            swap(ticket_number[i], ticket_number[j]);
            swap(name[i], name[j]);  // Swap corresponding name
            swap(purchase_date[i], purchase_date[j]);  // Swap corresponding purchase_date
        }

        // Place the pivot element in the correct position
        swap(ticket_number[l], ticket_number[j]);
        swap(name[l], name[j]);
        swap(purchase_date[l], purchase_date[j]);

        return j;
    }

    // QuickSort function to sort the ticket_number array
    void QuickSort(int l, int r) {
        if (l < r) {
            int s = Partition(l, r);
            QuickSort(l, s - 1);
            QuickSort(s + 1, r);
        }
    }

public:
    ticket_data();

    void welcome();
    void load_from_file();
    void display_data();
    void sort_data();  // Sort ticket data based on ticket_number
};

ticket_data::ticket_data() {
    global_count = 0;
}

void ticket_data::welcome() {
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tTICKET MANAGEMENT SYSTEM\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void ticket_data::load_from_file() {
    ifstream file("TicketData.txt");

    if (!file) {
        cout << "File Not Found\n";
        return;
    }

    // Correctly read the file data
    while (file.getline(name[global_count], 30, ',') &&
           file.getline(ticket_number[global_count], 15, ',') &&
           file.getline(purchase_date[global_count], 15)) {
        if (global_count < 150)
            global_count++;
        else {
            cout << "Maximum data limit reached.\n";
            break;
        }
    }

    file.close();
}

void ticket_data::display_data() {
    if (global_count == 0) {
        cout << "No data to display.\n";
        return;
    }

    cout << left << setw(30) << "Name"
         << setw(20) << "Ticket Number"
         << setw(15) << "Purchase Date" << endl;
    for (int i = 0; i < 80; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < global_count; i++) {
        cout << left << setw(30) << name[i]
             << setw(20) << ticket_number[i]
             << setw(15) << purchase_date[i] << endl;
    }
}

void ticket_data::sort_data() {
    if (global_count > 1) {
        // Call the QuickSort function to sort the ticket_number array and rearrange associated data
        QuickSort(0, global_count - 1);
    } else {
        cout << "Not enough data to sort.\n";
    }
}

int main() {
    ticket_data engine;
    engine.welcome();

    engine.load_from_file();

    cout << "\nBefore sorting:\n";
    engine.display_data();

    // Sort the tickets by ticket number
    engine.sort_data();

    cout << "\nAfter sorting:\n";
    engine.display_data();

    return 0;
}
