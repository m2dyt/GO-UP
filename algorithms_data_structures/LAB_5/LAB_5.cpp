#include <iostream>

using namespace std;

int cnt_q = 0; 
int swaps = 0;

void SwapElem(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    swaps++;
}

int PartSort(int arr[], int low, int high) {
    int pivot = arr[(high + low) / 2];
    int i = low;
    int j = high;
    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
            cnt_q++;
        }
        cnt_q++;
        while (arr[j] > pivot) {
            j--;
            cnt_q++;
        }
        cnt_q++;
        if (i <= j) {
            SwapElem(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    return i;
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

void SearchByIndex(int arr[], int n, int index) {
    if (index >= 0 && index < n)
        cout << "Элемент с индексом " << index << " = " << arr[index] << endl;
    else
        cout << "Ошибка: индекс вне диапазона!" << endl;
}

void SearchByValue(int arr[], int n, int value) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == value) {
            cout << "Элемент " << value << " найден на позиции " << i << endl;
            return;
        }
    }
    cout << "Элемент " << value << " не найден" << endl;
}

void AddElement(int arr[], int& n, int value) {
    arr[n] = value;
    n++;
    QuickSort(arr, 0, n - 1);
}

void DeleteElement(int arr[], int& n, int index) {
    if (index < 0 || index >= n) {
        cout << "Ошибка: индекс вне диапазона!" << endl;
        return;
    }
    for (int i = index; i < n - 1; i++)
        arr[i] = arr[i + 1];
    n--;
    QuickSort(arr, 0, n - 1);
}

int main() {
    setlocale(LC_ALL, "Russian");

    const int SIZE = 100;
    int arr[SIZE];
    int n;

    cout << "Введите количество элементов массива: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Введите элемент массива: ";
        cin >> arr[i];
    }

    while (true) {
        cout << "Меню:\n";
        cout << "1 - Показать массив\n";
        cout << "2 - Сортировка массива \n";
        cout << "3 - Поиск по индексу\n";
        cout << "4 - Поиск по значению\n";
        cout << "5 - Добавить элемент\n";
        cout << "6 - Удалить по индексу\n";
        cout << "0 - Выход\n";
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            PrintArr(arr, n);
        }
        else if (choice == 2) {
            cnt_q = swaps = 0;
            QuickSort(arr,0, n - 1);
            cout << "Массив отсортирован.\n";
            cout << "Сравнений: " << cnt_q << ", Перестановок: " << swaps << endl;
        }
        else if (choice == 3) {
            int idx;
            cout << "Введите индекс для поиска: ";
            cin >> idx;
            SearchByIndex(arr, n, idx);
        }
        else if (choice == 4) {
            int val;
            cout << "Введите значение для поиска: ";
            cin >> val;
            SearchByValue(arr, n, val);
        }
        else if (choice == 5) {
            cnt_q = swaps = 0;
            int val;
            cout << "Введите элемент для добавления: ";
            cin >> val;
            AddElement(arr, n, val);
            cout << "Элемент добавлен.\n";
            cout << "Сравнений: " << cnt_q << ", Перестановок: " << swaps << endl;
        }
        else if (choice == 6) {
            cnt_q = swaps = 0;
            int idx;
            cout << "Введите индекс для удаления: ";
            cin >> idx;
            DeleteElement(arr, n, idx);
            cout << "Элемент удалён.\n";
            cout << "Сравнений: " << cnt_q << ", Перестановок: " << swaps << endl;
        }
        else if (choice == 0) {
            cout << "Выход из программы.\n";
            break;
        }
        else {
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }

    return 0;
}
