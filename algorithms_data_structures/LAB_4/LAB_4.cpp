#include <iostream>
#include <random>
#include <fstream>
#include <locale>

using namespace std;

const int M = 3000;  // размер хеш-таблицы
const int KEY_SIZE = 7; 

// Состояния ячейки
const int EMPTY = 0;
const int OCCUPIED = 1;
const int DELETED = 2;


struct Cell {
    char key[KEY_SIZE]; // массив для хранения ключа
    int state = EMPTY;  // состояние 
};

Cell table[M];// хеш-таблица
int BadKeysCount = 0;
int hits[M] = {0};// счётчик попаданий в сегменты



void copyKey(char* dest, const char* src) {
    for (int i = 0; i < KEY_SIZE; i++) {
        dest[i] = src[i]; 
        if (src[i] == '\0') break; 
    }
}


bool isValidKey(char* key) {
    for (int i = 0; i < 6; i++) {
        if (key[i] == '\0') return false;
    }
    if (key[6] != '\0') return false;

    for (int i = 0; i < 3; i++) {
        if (key[i] < '0' || key[i] > '9') return false;
    }
    if (key[3] < 'A' || key[3] > 'Z') return false;
    if (key[4] < '0' || key[4] > '9') return false;
    if (key[5] < '0' || key[5] > '9') return false;

    return true;
}


// Полиномиальное хеширование
int computeHash(char* key) {
    long long h = 0;
    for (int i = 0; i < 6; i++) {
        long long code = (int)key[i];
        h += (i + 1) * code * code;
    }
    return (int)(h % M);
}


// Вставка ключа (квадратичное опробование)
bool insertKey(char* key) {
    if (!isValidKey(key)) {
        cout << "ключ " << key << " имеет неверный формат!\n";
        return false;
    }

    int h = computeHash(key);
    hits[h]++;

    int firstDeleted = -1;

    for (int i = 0; i < M; i++) {
        int idx = (h + i * i) % M;
        if (table[idx].state == EMPTY) {
            int pos;
            if (firstDeleted != -1) {
                pos = firstDeleted;
            }
            else {
                pos = idx;
            }
            copyKey(table[pos].key, key); 
            table[pos].state = OCCUPIED;
            return true;
        }
        if (table[idx].state == DELETED && firstDeleted == -1) {
            firstDeleted = idx;
        }
    }

    BadKeysCount++;
    cout << "ВНИМАНИЕ: таблица переполнена, ключ " << key << " не вставлен.\n";
    return false;
}


// Поиск ключа
int findKey(char* key) {
    if (!isValidKey(key)) return -1;
    int h = computeHash(key);
    for (int i = 0; i < M; i++) {
        int idx = (h + i * i) % M;
        if (table[idx].state == EMPTY) return -1;
        if (table[idx].state == OCCUPIED) {
            bool equal = true;
            for (int j = 0; j < KEY_SIZE; j++) {
                if (table[idx].key[j] != key[j]) {
                    equal = false;
                    break;
                }
                if (key[j] == '\0') break;
            }
            if (equal) return idx;
        }
    }
    return -1;
}


// Поиск по сегменту
void findBySegment(int seg) {
    if (seg < 0 || seg >= M) {
        cout << "Ошибка: сегмент вне диапазона [0.." << M - 1 << "]\n";
        return;
    }
    if (table[seg].state == OCCUPIED)
        cout << "Сегмент " << seg << ": ключ = " << table[seg].key << "\n";
    else if (table[seg].state == DELETED)
        cout << "Сегмент " << seg << ": [удалён]\n";
    else
        cout << "Сегмент " << seg << ": [пусто]\n";
}

// Удаление ключа
bool deleteKey(char* key) {
    int pos = findKey(key);
    if (pos == -1) return false;
    table[pos].state = DELETED;
    return true;
}


// Генерация случайного ключа
void generateKey(char* key, mt19937& gen) {
    uniform_int_distribution<int> digit(0, 9);
    uniform_int_distribution<int> letter(0, 25);

    key[0] = '0' + digit(gen);
    key[1] = '0' + digit(gen);
    key[2] = '0' + digit(gen);
    key[3] = 'A' + letter(gen);
    key[4] = '0' + digit(gen);
    key[5] = '0' + digit(gen);
    key[6] = '\0';
}

// Экспорт hits.txt
void exportHits() {
    ofstream fout("hits.txt");
    for (int i = 0; i < M; i++) {
        fout << hits[i] << "\n";
    }
    fout.close();
    cout << "Файл hits.txt сохранён для построения гистограммы в Excel.\n";
}
 
// Печать таблицы
void showTable() {
    for (int i = 0; i < M; i++) {
        cout << i << ": ";
        if (table[i].state == OCCUPIED) cout << table[i].key;
        else if (table[i].state == DELETED) cout << "[deleted]";
        else cout << "[empty]";
        cout << "\n";
    }
}


// Меню
void menu() {
    cout << "\n===== МЕНЮ =====\n";
    cout << "1. Сгенерировать N случайных ключей\n";
    cout << "2. Вставить ключ вручную\n";
    cout << "3. Найти ключ\n";
    cout << "4. Удалить ключ\n";
    cout << "5. Показать количество BadKeys\n";
    cout << "6. Экспортировать hits.txt для Excel\n";
    cout << "7. Просмотреть всю таблицу\n";
    cout << "8. Поиск по номеру сегмента\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}


int main() {
    setlocale(LC_ALL, "Russian");
    mt19937 gen(random_device{}());

    int choice = -1;
    while (true) {
        menu();
        cin >> choice;

        if (choice == 0) {
            cout << "Выход из программы.\n";
            break;
        }
        else if (choice == 1) {
            int N;
            cout << "Введите количество случайных ключей: ";
            cin >> N;
            for (int i = 0; i < N; i++) {
                char key[KEY_SIZE];
                generateKey(key, gen);
                insertKey(key);
            }
            cout << "Сгенерировано и вставлено " << N << " ключей.\n";
        }
        else if (choice == 2) {
            char key[KEY_SIZE];
            cout << "Введите ключ (формат цццБцц): ";
            cin >> key;
            if (insertKey(key))
                cout << "Ключ " << key << " вставлен.\n";
            else
                cout << "Не удалось вставить ключ " << key << ".\n";
        }
        else if (choice == 3) {
            char key[KEY_SIZE];
            cout << "Введите ключ для поиска: ";
            cin >> key;
            int pos = findKey(key);
            if (pos != -1)
                cout << "Ключ найден в сегменте " << pos << ".\n";
            else
                cout << "Ключ не найден.\n";
        }
        else if (choice == 4) {
            char key[KEY_SIZE];
            cout << "Введите ключ для удаления: ";
            cin >> key;
            if (deleteKey(key))
                cout << "Ключ удалён.\n";
            else
                cout << "Ключ не найден.\n";
        }
        else if (choice == 5) {
            cout << "Количество BadKeys: " << BadKeysCount << "\n";
        }
        else if (choice == 6) {
            exportHits();
        }
        else if (choice == 7) {
            showTable();
        }
        else if (choice == 8) {
            int seg;
            cout << "Введите номер сегмента: ";
            cin >> seg;
            findBySegment(seg);
        }
        else {
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
    return 0;
}
