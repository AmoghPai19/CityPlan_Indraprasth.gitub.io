#include <iostream>
#include <fstream>
using namespace std;

void heapify(int a[], int n) {
    int k, heap, v, j;
    for (int i = n / 2; i >= 1; i--) {
        k = i;
        v = a[k];
        heap = 0;
        while (heap != 1 && 2 * k <= n) {
            j = 2 * k;
            if (j < n) {
                if (a[j] < a[j + 1])
                    j = j + 1;
            }
            if (v >= a[j])
                heap = 1;
            else {
                a[k] = a[j];
                k = j;
            }
        }
        a[k] = v;
    }
}

int main() {
    int a[100]; // Start indexing from 1
    int n = 0;

    ifstream file("wheat_qua.txt");

    if (!file) {
        cout << "File Not Found\n";
        return 1;
    }

    string line;
    cout << "Reading data from file:\n";
    while (getline(file, line)) {
        int id, quality;
        sscanf(line.c_str(), "%d, %d", &id, &quality);
        cout << "ID: " << id << ", Quality: " << quality << endl; // Debug print
        a[++n] = quality; // Add quality value to heap array
    }
    file.close();

    heapify(a, n);

    cout << "Max Heap:" << endl;
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << endl;

    return 0;
}
