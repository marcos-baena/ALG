#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
/**************************************/

void quicksort(vector<int> &v, int left, int right)
{
    if (left >= right)
        return;
    int pivot = v[right];
    int partitionIndex = left;
    for (int i = left; i < right; ++i)
    {
        if (v[i] < pivot)
        {
            swap(v[i], v[partitionIndex]);
            ++partitionIndex;
        }
    }
    swap(v[partitionIndex], v[right]);
    quicksort(v, left, partitionIndex - 1);
    quicksort(v, partitionIndex + 1, right);
}

int getSmallestNumber(vector<int> v, int k)
{
    quicksort(v, 0, v.size() - 1);
    string result = "";
    for (int i = 0; i < k; ++i)
    {
        result += to_string(v[i]);
    }
    return stoi(result);
}


int main(int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();

    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <size_of_vector>" << endl;
        return 1;
    }

    int size = stoi(argv[1]);
    if (size <= 0)
    {
        cerr << "Size of vector must be a positive integer." << endl;
        return 1;
    }

    srand(time(0));
    vector<int> v(size);
    for (int i = 0; i < size; ++i)
    {
        v[i] = rand() % 9 + 1; // Random values from 1 to 9
    }

    int SmallestNumber = getSmallestNumber(v, min(4, size));

    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Print out the elapsed time
    std::cout << duration.count() << std::endl;

    return 0;
}