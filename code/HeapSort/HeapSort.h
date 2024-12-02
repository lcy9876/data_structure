#include <iostream>
#include <vector>


using namespace std;

bool check(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if (vec[i] > vec[i + 1]) {
            return false; 
        }
    }
    return true; 
}

void printlist(std::vector<int>& arr, int a, int b) {
    for (int i = a; i < b; ++i) {
        std::cout << arr[i] << " ";
    }

}


void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    
    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}