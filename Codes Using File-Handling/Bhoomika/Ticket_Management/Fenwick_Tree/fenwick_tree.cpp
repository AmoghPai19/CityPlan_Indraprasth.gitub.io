#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_SIZE = 150; // Maximum number of entries

// Fenwick Tree class
class fenwick {
public:
    fenwick(int n);
    void update(int x, int delta);
    int query(int x);
    int sum();

private:
    int BIT[MAX_SIZE]; // Binary Indexed Tree
    int n;             // Size of the tree
};

fenwick::fenwick(int n) : n(n) {
    for (int i = 0; i <= n; i++) {
        BIT[i] = 0;
    }
}

void fenwick::update(int x, int delta) {
    for (; x <= n; x += x & -x)
        BIT[x] += delta;
}

int fenwick::query(int x) {
    int sum = 0;
    while (x > 0) {
        sum += BIT[x];
        x -= x & -x;
    }
    return sum;
}

int fenwick::sum() {
    return query(n);
}

// Ticket Management class
class ticket_data {
private:
    string name[MAX_SIZE];
    int ticket_cost[MAX_SIZE];
    int ticket_number[MAX_SIZE];
    int global_count;

public:
    ticket_data();
    void load_from_file(const string &filename);
    void display_data(fenwick &fen);
};

ticket_data::ticket_data() : global_count(0) {}

void ticket_data::load_from_file(const string &filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Error: File '" << filename << "' not found.\n";
        return;
    }

    cout << "Loading data from '" << filename << "'...\n";

    // Read data from the file
    while (file >> name[global_count] >> ticket_cost[global_count] >> ticket_number[global_count]) {
        global_count++;
        if (global_count >= MAX_SIZE) {
            cout << "Warning: Maximum number of entries (" << MAX_SIZE << ") reached.\n";
            break;
        }
    }

    file.close();

    if (global_count == 0) {
        cout << "Error: No data found in '" << filename << "' or file format is incorrect.\n";
    } else {
        cout << "Successfully loaded " << global_count << " entries.\n";
    }
}

void ticket_data::display_data(fenwick &fen) {
    cout << left << setw(30) << "Name"
         << setw(15) << "Ticket Cost"
         << setw(20) << "Ticket Number"
         << setw(15) << "Cumulative Cost" << endl;
    for (int i = 0; i < 80; i++)
        cout << "-";
    cout << endl;

    // Initialize Fenwick Tree with the correct size
    fenwick tree(global_count);

    for (int i = 0; i < global_count; i++) {
        tree.update(i + 1, ticket_cost[i]); // Update Fenwick Tree
        cout << left << setw(30) << name[i]
             << setw(15) << ticket_cost[i]
             << setw(20) << ticket_number[i]
             << setw(15) << tree.query(i + 1) << endl; // Query cumulative sum up to i + 1
    }

    cout << "\nTotal ticket cost: " << tree.sum() << endl;
}

int main() {
    ticket_data engine;

    // Ensure the file exists and is properly formatted
    string filename = "TicketPrices.txt";
    engine.load_from_file(filename); // Load data from the file

    fenwick fen(MAX_SIZE); // Fenwick Tree with maximum size
    engine.display_data(fen); // Display ticket data with cumulative sums

    return 0;
}
