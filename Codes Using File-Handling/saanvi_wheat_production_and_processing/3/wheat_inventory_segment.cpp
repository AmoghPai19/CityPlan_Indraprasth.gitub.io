#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define MAX 1000

class segtree
{
public:
    int size;
    int tree[MAX * 4];
    int lazy[MAX * 4]; 

    void build(int index, int low, int high, int arr[]);
    void update_range(int index, int low, int high, int l, int r, int val);
    void propagate(int index, int low, int high);
    void display(int index, int low, int high);
    segtree(int n, int arr[]);
};

segtree::segtree(int n, int arr[])
{
    size = n;
    for (int i = 0; i < MAX * 4; i++)
    {
        tree[i] = 0;
        lazy[i] = 0;
    }
    build(0, 0, n - 1, arr);
}

void segtree::build(int index, int low, int high, int arr[])
{
    if (low == high)
    {
        tree[index] = arr[low];
    }
    else
    {
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
    }
}

void segtree::propagate(int index, int low, int high)
{
    if (lazy[index] != 0)
    {
        tree[index] += (high - low + 1) * lazy[index];
        if (low != high)
        {
            lazy[2 * index + 1] += lazy[index];
            lazy[2 * index + 2] += lazy[index];
        }
        lazy[index] = 0;
    }
}

void segtree::update_range(int index, int low, int high, int l, int r, int val)
{
    propagate(index, low, high);

    if (low > r || high < l) return;

    if (low >= l && high <= r)
    {
        tree[index] += (high - low + 1) * val;
        if (low != high)
        {
            lazy[2 * index + 1] += val;
            lazy[2 * index + 2] += val;
        }
        return;
    }

    int mid = (low + high) / 2;
    update_range(2 * index + 1, low, mid, l, r, val);
    update_range(2 * index + 2, mid + 1, high, l, r, val);
    tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
}

void segtree::display(int index, int low, int high)
{
    propagate(index, low, high);
    if (low == high)
    {
        cout << "Value at index " << low + 1 << " : " << tree[index] << "kg" << endl;
        return;
    }
    int mid = (low + high) / 2;
    display(2 * index + 1, low, mid);
    display(2 * index + 2, mid + 1, high);
}

int main()
{
    int arr[MAX];
    int n = 0;

    ifstream file("wheat_qua.txt");
    if (!file)
    {
        cout << "File Not Found\n";
        return 1;
    }

    string line;
    cout << "Reading data from file:\n";
    while (getline(file, line))
    {
        char batch[10];
        int quality;
        sscanf(line.c_str(), "%s %dkg", batch, &quality);
        cout << "Batch: " << batch << ", Quality: " << quality << endl;
        arr[n++] = quality;
    }
    file.close();

    segtree segmenttree(n, arr);

    int q;
    cout << "Enter the number of queries: ";
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int choice;
        cout << "1. Update range\n2. Display\nEnter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            int l, r, val;
            cout << "Enter the range (l r) and value to add: ";
            cin >> l >> r >> val;
            segmenttree.update_range(0, 0, n - 1, l - 1, r - 1, val);
            cout << "Range updated.\n";
        }
        else if (choice == 2)
        {
            segmenttree.display(0, 0, n - 1);
        }
    }

    return 0;
}
