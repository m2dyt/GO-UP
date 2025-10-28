#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// обход графа в ширину кол-во оповещённых сотрудников
int bfs(const vector<vector<int>>& matrix, int start, int days, int maxPerDay) {
    int n = matrix.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q; // (номер сотрудника, день оповещения)

    visited[start] = true;
    q.push({ start, 0 }); 

    int count = 1; // стартовый сотрудник уже оповещён

    while (!q.empty()) {
        int current = q.front().first;
        int day = q.front().second;
        q.pop();

        // если достигли лимита по дням — прекращаем
        if (day == days) continue;

        int notifiedToday = 0;

        for (int i = 0; i < n; ++i) {
            if (matrix[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push({ i, day + 1 });
                count++;
                notifiedToday++;
                if (notifiedToday == maxPerDay) break; // максимум 3 человека в день
            }
        }
    }
    return count;
}


// вывод матрицы смежности
void printMatrix(const vector<vector<int>>& matrix, const vector<string>& names) {
    int n = matrix.size();
    cout << "\nМатрица смежности:\n";
    cout << setw(10) << " ";
    for (int i = 0; i < n; ++i)
        cout << setw(10) << names[i];
    cout << "\n";

    for (int i = 0; i < n; ++i) {
        cout << setw(10) << names[i];
        for (int j = 0; j < n; ++j)
            cout << setw(10) << matrix[i][j];
        cout << "\n";
    }
}



void inputData(vector<string>& names, vector<vector<int>>& matrix, map<string, int>& nameToIndex) {
    int n = names.size();

    cout << "Введите фамилии сотрудников:\n";
    for (int i = 0; i < n; ++i) {
        cout << i + 1 << ". ";
        cin >> names[i];
        nameToIndex[names[i]] = i;
    }

    cout << "\nВведите связи в формате: фамилия_оповещающего фамилия_оповещаемого\n";
    cout << "(Введите слово END, чтобы закончить ввод)\n";

    while (true) {
        string from, to;
        cout << "> ";
        cin >> from;
        if (from == "end") break;
        cin >> to;

        if (nameToIndex.find(from) == nameToIndex.end() || nameToIndex.find(to) == nameToIndex.end()) {
            cout << "Ошибка: фамилия не найдена!\n";
            continue;
        }

        int i = nameToIndex[from];
        int j = nameToIndex[to];
        matrix[i][j] = 1;
    }
}


// проверка полноты списка оповещения
void checkFullAlert(const vector<vector<int>>& matrix, const map<string, int>& nameToIndex, const vector<string>& names) {
    string startName;
    cout << "Введите фамилию сотрудника, с которого начинается оповещение: ";
    cin >> startName;

    if (nameToIndex.find(startName) == nameToIndex.end()) {
        cout << "Ошибка: фамилия не найдена!\n";
        return;
    }

    int start = nameToIndex.at(startName);
    int totalReached = bfs(matrix, start, matrix.size(), 3);

    if (totalReached == matrix.size())
        cout << "все сотрудники будут оповещены.\n";
    else
        cout << "Список неполон. Оповещено только " << totalReached << " из " << matrix.size() << " сотрудников.\n";
}

// расчёт оповещённых за K дней
void countAlertForDays(const vector<vector<int>>& matrix, const map<string, int>& nameToIndex, const vector<string>& names) {
    string startName;
    cout << "Введите фамилию сотрудника, с которого начинается оповещение: ";
    cin >> startName;

    if (nameToIndex.find(startName) == nameToIndex.end()) {
        cout << "Ошибка: фамилия не найдена!\n";
        return;
    }

    int K;
    cout << "Введите количество дней K: ";
    cin >> K;

    int start = nameToIndex.at(startName);
    int totalReached = bfs(matrix, start, K, 3);

    cout << "За " << K << " дней будет оповещено " << totalReached << " человек(а).\n";
}


int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество сотрудников: ";
    cin >> n;

    vector<string> names(n);
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    map<string, int> nameToIndex;

    inputData(names, matrix, nameToIndex);

    while (true) {
        cout << "МЕНЮ\n";
        cout << "1. Проверить, полон ли список оповещения\n";
        cout << "2. Посчитать, сколько людей будет оповещено за K дней\n";
        cout << "3. Вывести матрицу смежности\n";
        cout << "0. Выход\n";
        cout << "Выберите пункт: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) checkFullAlert(matrix, nameToIndex, names);
        else if (choice == 2) countAlertForDays(matrix, nameToIndex, names);
        else if (choice == 3) printMatrix(matrix, names);
        else cout << "Неверный пункт меню!\n";
    }

    cout << "Программа завершена.";
    return 0;
}
