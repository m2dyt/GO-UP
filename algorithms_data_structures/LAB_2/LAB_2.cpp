#include <iostream>
#include <cmath>

struct Node {
    int data;
    Node* next;
};


void PushBack(Node*& head, int value) {
    Node* new_node = new Node{ value, nullptr };
    if (!head) {
        head = new_node;
    }
    else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}


bool PopBack(Node*& head) {
    if (!head) {
        return false;
    }
    if (!head->next) {
        delete head;
        head = nullptr;
        return true;
    }
    Node* temp = head;
    while (temp->next->next) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    return true;


}


void PrintNode(Node* head) {
    if (!head) {
        std::cout << "ТУТ ПУСТО\n";
    }
    else {
        Node* temp = head;
        while (temp) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << '\n';
    }
}



double LabCh(Node* head) {
    double sum = 0;
    int n = 0;
    Node* temp = head;
    
    while (temp) {
        sum += temp->data;
        n++;
        temp = temp->next;
    }

    double a_mid = sum / n;
    double rez = INFINITY;
    temp = head;
    while(temp){
        double rez_1 = std::fabs(temp->data - a_mid);
        rez = std::min(rez, rez_1);
        temp = temp->next;
    }
    return rez;
}

int main()
{
    setlocale(LC_ALL, "rus");
    Node* head = nullptr;
    int choose = -1;
    
    while (choose != 0) {
        std::cout << "1. Добавить элемент в конец\n";
        std::cout << "2. Удалить последний элемент\n";
        std::cout << "3. Показать список\n";
        std::cout << "4. Найти минимальное |ai - aq|\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choose;
        switch (choose) {
        case 0: {
            std::cout << "Выход\n";
            choose = 0;
            break;
        }
        case 1: {
            int value;
            std::cout << "Введите число ";
            std::cin >> value;
            PushBack(head, value);
            break;
        }
        case 2: {
            if (PopBack(head)) {
                std::cout << "Последний элемент удалён\n";
            }
            else {
                std::cout << "Список пуст\n";
            }
            break;
        }
        case 3: {
            std::cout << "Список\n";
            PrintNode(head);
            break;
        }
        case 4: {
            if (!head) {
                std::cout << "Список пуст.\n";
            }
            else {
                
                std::cout << "Минимальное |ai - aq| = " << LabCh(head) << std::endl;
            }
            break;
        }
        default: {
            std::cout << "Неверный выбор!\n";
        }
        }
    }
}

