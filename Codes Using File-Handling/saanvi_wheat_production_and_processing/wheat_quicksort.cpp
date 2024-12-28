#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

class wheat_quality_data {
private:
    char batch_id[150][30];
    char quality_type[150][30];
    int quality_value[150];
    int global_count;

public:
    wheat_quality_data();
    void welcome();
    void load_from_file();
    void display_data();
    void sort_data();
    void quicksort(int quality_value[], int l, int r);
    int partition(int quality_value[], int l, int r);
};

wheat_quality_data::wheat_quality_data() {
    global_count = 0;
}

void wheat_quality_data::welcome() {
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tWHEAT QUALITY DATA\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void wheat_quality_data::load_from_file() {
    ifstream file("wheat_quality.txt");

    if (!file) {
        cout << "File Not Found\n";
        return;
    }

    while (file >> batch_id[global_count]
                >> quality_type[global_count]
                >> quality_value[global_count]) {
        if (global_count < 150)
            global_count++;
        else {
            cout << "Maximum data limit reached.\n";
            break;
        }
    }

    file.close();
}

void wheat_quality_data::display_data() {
    for (int i = 0; i < global_count; i++) {
        cout << setw(20) << batch_id[i]
             << setw(20) << quality_type[i]
             << setw(10) << quality_value[i] << endl;
    }
}

void wheat_quality_data::sort_data() {
    quicksort(quality_value, 0, global_count - 1);

    cout << "After sorting by quality value:" << endl;
    for (int i = 0; i < global_count; i++) {
        cout << setw(20) << batch_id[i]
             << setw(20) << quality_type[i]
             << setw(10) << quality_value[i] << endl;
    }
}

int wheat_quality_data::partition(int quality_value[], int l, int r) {
    int p = quality_value[l];
    int i = l;
    int j = r + 1;

    while (true) {
        while (i < r && quality_value[++i] < p);
        while (j > l && quality_value[--j] > p);

        if (i >= j) {
            break;
        }

        swap(quality_value[i], quality_value[j]);
        swap(batch_id[i], batch_id[j]);
        swap(quality_type[i], quality_type[j]);
    }

    swap(quality_value[l], quality_value[j]);
    swap(batch_id[l], batch_id[j]);
    swap(quality_type[l], quality_type[j]);
    return j;
}

void wheat_quality_data::quicksort(int quality_value[], int l, int r) {
    if (l < r) {
        int j = partition(quality_value, l, r);
        quicksort(quality_value, l, j - 1);
        quicksort(quality_value, j + 1, r);
    }
}

int main() {
    wheat_quality_data engine;
    engine.welcome();

    engine.load_from_file();
    engine.display_data();

    engine.sort_data();
    return 0;
}
