#include <iostream>
#include <cstdlib>

struct Task {
    int id;
    int arr_time; //  время поступления в систему
    int p0_time;//  время выполнения на процессоре P0
    int p1_time;// время выполнения на процессоре P1
    int rem_time; // оставшееся время выполнения на текущем процессоре
    int stage; // 0 = P0        1 = P1
    // СТРУКТУРА ТАСКИ
};


struct Node {
    Task task;
    Node* next;

    Node(Task t) : task(t), next(nullptr){} // СТРУКТУРА УЗЛА 
};


class Stack {
private:
    Node* top_node;// вершина стэка
public:
    Stack() : top_node(nullptr) {} // КОНСТРУКТОР 

    bool empty() { 
        return (top_node == nullptr); // ПУСТОЙ ЛИ 
    }

    void push(Task t) { 
        Node* new_node = new Node(t);
        new_node->next = top_node;
        top_node = new_node;  // ДОБАВЛЕНИЕ В СТЭК 
    }

    Task pop() {
        if (empty()) {
            Task dum;
            dum.id = -1;
            return dum;
        }

        Node* temp = top_node; 
        Task t = temp->task; 
        top_node = top_node->next;
        delete temp;// удаляем старую вершину
        return t; // ИЗВЛЕКАЕМ ТАСКУ
    }

    void print() {
        Node* current = top_node;
        while (current) {
            std::cout << "id#" << current->task.id << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};


class Queue {
private:
    Node* head;
    Node* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {} // КОНСТРУКТОР 

    bool empty() {
        return head == nullptr;  // ПУСТОЙ ЛИ 
    }

    void push(Task t) {
        Node* new_node = new Node(t);
        if (empty()) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node; // ДОБАВЛЕНИЕ В ОЧЕРЕДЬ
        }
    }

    Task pop() {
        if (empty()) {
            Task dummy; 
            dummy.id = -1;   
            return dummy; 
        }

        Node* temp = head;
        Task t = temp->task;
        head = temp->next;
        if (!head) {
            tail = nullptr; // если стэк пустой занулить хвост
        }
        delete temp;
        return t;  // ИЗВЛЕКАЕМ ТАСКУ

    }

    void print() {
        Node* current = head;
        while (current) {
            std::cout << "id#" << current->task.id << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};


class Processor {
private:
    bool busy; // занят или свободен процессо
    Task current_task; // задача которая сейчас выполняется
public:
    Processor() : busy(false){}

    bool isBusy() {
        return busy;
    }

    void newTask(Task t) {
        current_task = t;
        busy = true; // Назначить задачу процессору
    }

    bool tick() { // ОДИН ТИК РАБОТЫ 
        if (!busy) {
            return false;// процессор свободен 
        }
        current_task.rem_time--;
        if (current_task.rem_time <= 0) {
            busy = false;
            return true; // если время вышло процессор освобождается и задача завершена
        }
        return false;
    }

    Task gettask() {
        return current_task;
    }

    void printStatus(const std::string& name) {
        if (busy) {
            std::cout << name << " выполняет задачу id#" << current_task.id
                << " осталось " << current_task.rem_time << "\n";
        }
        else {
            std::cout << name << " свободен\n";
        }
    }

};


int main()
{   
    setlocale(LC_ALL, "rus");
    Stack S;
    Queue Q;
    Processor P0, P1;

    int time = 0;
    int task_id = 1;

    while (true) {
        std::cout << "Время: " << time << "\n";
        std::cout << "Меню:\n";
        std::cout << "1. Добавить задачу вручную\n";
        std::cout << "2. Сгенерировать случайную задачу\n";
        std::cout << "3. Следующий такт\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice == 1) {
            Task t;
            t.id = task_id;
            task_id++;
            t.arr_time = time;
            std::cout << "Введите время для P0 ";
            std::cin >> t.p0_time;
            std::cout << "Введите время для P1 ";
            std::cin >> t.p1_time;
            t.rem_time = t.p0_time;
            t.stage = 0;
            S.push(t);
            std::cout << "Задача id#" << t.id << " добавлена в стек.\n";
        }

        if (choice == 2) {
            Task t;
            t.id = task_id;
            task_id++;
            t.arr_time = time;
            t.p0_time = 1 + rand() % 4;
            t.p1_time = 1 + rand() % 4;
            t.rem_time = t.p0_time;
            t.stage = 0;
            S.push(t);
            std::cout << "Случайная задача id#" << t.id
                << " P0=" << t.p0_time
                << ", P1=" << t.p1_time << " добавлена в стек.\n";
        }

        if (choice == 3) { // Если процессор P0 свободен, он пытается взять задачу из стека
            if (!P0.isBusy()) {
                Task t = S.pop(); // берем таску 
                if (t.id != -1) { // проверка было ли что-то в стэке
                    t.rem_time = t.p0_time;
                    t.stage = 0;
                    P0.newTask(t);
                    std::cout << "P0 взял задачу id#" << t.id << "\n";
                }
            }   

            if (!P1.isBusy()) { // Если процессор P1 свободен, он пытается взять задачу из очереди
                Task t = Q.pop();
                if (t.id != -1) { // проверка было ли что-то в очереди
                    t.rem_time = t.p1_time;
                    t.stage = 1;
                    P1.newTask(t);
                    std::cout << "P1 взял задачу id#" << t.id << "\n";
                }
            }

            if (P0.tick()) {
                Task finish = P0.gettask();
                finish.rem_time = finish.p1_time;
                finish.stage = 1;
                Q.push(finish);
                std::cout << "P0 завершил задачу id#" << finish.id
                << " и отправил её в очередь\n";
            }

            if (P1.tick()) {
                Task finish = P1.gettask();
                std::cout << "P1 завершил задачу id#" << finish.id << "\n";
            }

            std::cout << " СОСТОЯНИЕ ПРОГРАММЫ \n";
            P0.printStatus("P0");
            P1.printStatus("P1");
            std::cout << "Стек: "; S.print(); std::cout << "\n";
            std::cout << "Очередь: "; Q.print(); std::cout << "\n";

            time++;
        }
    }
    
}
