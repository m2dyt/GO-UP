#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <locale>

using namespace std;

const int M = 3000; // размер хеш-таблицы

// Состояние ячейки хеш-таблицы
enum CellState { EMPTY, OCCUPIED, DELETED };


struct Cell {
    string key;
    CellState state = EMPTY; // состояние: пусто, занято или удалено
};


vector<Cell> table(M); // сама хеш-таблица
vector<string> BadKeys; // список ключей, которые не удалось вставить
vector<int> hits(M, 0); // количество попаданий в каждый сегмент для анализа распределения

// Проверка ключа 
bool isValidKey(const string& key) {
    if (key.size() != 6) return false;   
    for (int i = 0; i < 3; i++) if (!isdigit(key[i])) return false; 
    if (!(key[3] >= 'A' && key[3] <= 'Z')) return false;            
    if (!isdigit(key[4]) || !isdigit(key[5])) return false;         
    return true;
}

// Полиномиальное хеширование 
int computeHash(const string& key) {
    long long h = 0;
    for (int i = 0; i < 6; i++) {
        long long code = (int)key[i]; // берем код ASCII символа
        h += (i + 1) * code * code; 
    }
    return (int)(h % M); 
}

// Вставка ключа с квадратичным опробованием
bool insertKey(const string& key) {
    if (!isValidKey(key)) {  
        cout << "ключ " << key << " имеет неверный формат!\n";
        return false;
    }

    int h = computeHash(key); // вычисляем хеш
    hits[h]++;                 // увеличиваем счетчик попаданий в сегмент

    int firstDeleted = -1;     // сохраняем индекс первой удалённой ячейки

    for (int i = 0; i < M; i++) {
        int idx = (h + i * i) % M; // квадратичное опробование
        if (table[idx].state == EMPTY) {
            int pos;
            if (firstDeleted != -1) {
                pos = firstDeleted;
            }
            else {
                pos = idx;
            } 
            table[pos].key = key;
            table[pos].state = OCCUPIED;
            return true;
        }
        if (table[idx].state == OCCUPIED && table[idx].key == key) {
            return true; // ключ уже есть
        }
        if (table[idx].state == DELETED && firstDeleted == -1) {
            firstDeleted = idx; // запоминаем первую удалённую ячейку
        }
    }

    
    BadKeys.push_back(key);
    cout << "ВНИМАНИЕ: таблица переполнена, ключ " << key << " не вставлен.\n";
    return false;
}

// Поиск ключа в таблице, возвращает индекс сегмента или -1, если не найден
int findKey(const string& key) {
    if (!isValidKey(key)) return -1;
    int h = computeHash(key);
    for (int i = 0; i < M; i++) {
        int idx = (h + i * i) % M; // квадратичное опробование
        if (table[idx].state == EMPTY) return -1; // пустая ячейка → ключ не найден
        if (table[idx].state == OCCUPIED && table[idx].key == key) return idx; // найден
    }
    return -1; // не найден после полного обхода
}

// Поиск по номеру сегмента
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

// Удаление ключа (помечаем как DELETED)
bool deleteKey(const string& key) {
    int pos = findKey(key);
    if (pos == -1) return false;
    table[pos].state = DELETED;
    return true;
}

// Генерация случайного ключа 
string generateKey(mt19937& gen) {
    uniform_int_distribution<int> digit(0, 9);
    uniform_int_distribution<int> letter(0, 25);

    string key;
    key += char('0' + digit(gen)); // цифра
    key += char('0' + digit(gen));
    key += char('0' + digit(gen));
    key += char('A' + letter(gen)); // буква
    key += char('0' + digit(gen));
    key += char('0' + digit(gen));
    return key;
}

// Экспорт количества попаданий в сегменты в файл hits.txt для построения гистограммы
void exportHits() {
    ofstream fout("hits.txt");
    for (int i = 0; i < M; i++) {
        fout << hits[i] << "\n";
    }
    fout.close();
    cout << "Файл hits.txt сохранён для построения гистограммы в Excel.\n";
}

// Экспорт всей таблицы в файл table.txt
void exportTable() {
    ofstream fout("table.txt");
    for (int i = 0; i < M; i++) {
        fout << i << " ";
        if (table[i].state == OCCUPIED) fout << table[i].key;
        else if (table[i].state == DELETED) fout << "[deleted]";
        else fout << "[empty]";
        fout << "\n";
    }
    fout.close();
    cout << "Файл table.txt сохранён (содержимое таблицы).\n";
}

// Вывод таблицы на экран
void showTable() {
    for (int i = 0; i < M; i++) {
        cout << i << ": ";
        if (table[i].state == OCCUPIED) cout << table[i].key;
        else if (table[i].state == DELETED) cout << "[deleted]";
        else cout << "[empty]";
        cout << "\n";
    }
}


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
    cout << "9. Экспортировать таблицу (table.txt)\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "Russian"); 
    mt19937 gen(random_device{}()); // генератор случайных чисел

    int choice = -1;

    while (true) { 
        menu();
        cin >> choice;

        if (choice == 0) { // выход
            cout << "Выход из программы.\n";
            break;
        }
        else if (choice == 1) { // генерация N случайных ключей
            int N;
            cout << "Введите количество случайных ключей: ";
            cin >> N;
            for (int i = 0; i < N; i++) {
                string key = generateKey(gen);
                insertKey(key);
            }
            cout << "Сгенерировано и вставлено " << N << " ключей.\n";
        }
        else if (choice == 2) { // вставка ключа вручную
            string key;
            cout << "Введите ключ (формат цццБцц): ";
            cin >> key;
            if (insertKey(key))
                cout << "Ключ " << key << " вставлен.\n";
            else
                cout << "Не удалось вставить ключ " << key << ".\n";
        }
        else if (choice == 3) { // поиск ключа
            string key;
            cout << "Введите ключ для поиска: ";
            cin >> key;
            int pos = findKey(key);
            if (pos != -1)
                cout << "Ключ найден в сегменте " << pos << ".\n";
            else
                cout << "Ключ не найден.\n";
        }
        else if (choice == 4) { // удаление ключа
            string key;
            cout << "Введите ключ для удаления: ";
            cin >> key;
            if (deleteKey(key))
                cout << "Ключ удалён.\n";
            else
                cout << "Ключ не найден.\n";
        }
        else if (choice == 5) { // показать BadKeys
            cout << "Количество BadKeys: " << BadKeys.size() << "\n";
        }
        else if (choice == 6) { // экспорт hits.txt
            exportHits();
        }
        else if (choice == 7) { // показать всю таблицу
            showTable();
        }
        else if (choice == 8) { // поиск по сегменту
            int seg;
            cout << "Введите номер сегмента: ";
            cin >> seg;
            findBySegment(seg);
        }
        else if (choice == 9) { // экспорт таблицы
            exportTable();
        }
        else {
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }

    return 0;
}
