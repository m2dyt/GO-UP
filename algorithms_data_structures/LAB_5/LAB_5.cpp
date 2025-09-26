#include <iostream>
using namespace std;

int cnt_q = 0; 
int swaps = 0;

int PartSort(int arr[], int low, int high) {

}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int index = PartSort(arr, low, high);
        if (low < index - 1) QuickSort(arr, low, index - 1);
        if (index < high) QuickSort(arr, index, high);
    }
}

void PrintArr(int arr[], int n) {
    cout << "Массив\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main()
{   
    setlocale(LC_ALL, "Russian");
    const int size_n = 100;
    int arr[size_n];
    int n;
    cout << "Введите количество элементов массива: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Введите элемент массива ";
        cin >> arr[i];
    }

    PrintArr(arr, n);
    
}
