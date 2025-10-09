#include <iostream>
using namespace std;

struct Node {
    int key;// Значение узла
    Node* left;// Указатель на левого потомка
    Node* right;// Указатель на правого потомка
    int height;// Высота узла
    Node* next;// для реализации очереди BFS

    Node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
        next = nullptr;
    }
};  


class Queue {
private:
    Node* head;
    Node* tail;
public:
    Queue() { 
        head = nullptr, tail = nullptr; 
    }

    bool IsEmpty() { 
        return head == nullptr;
    }

    void push(Node* node) {
        node->next = nullptr;
        if (IsEmpty()) {
            head = node;
            tail = node;
        }
        else {
            tail->next = node;
            tail = node;
        }
    }

    Node* pop() {
        if (IsEmpty()) return nullptr;
        Node* temp = head;
        head = head->next;
        if (head == nullptr) tail = nullptr;
        return temp;
    }
};

void updateHeight(Node* node) {
    if (node == nullptr) return; 
    int lh = (node->left != nullptr) ? node->left->height : 0;  // Высота левого поддерева
    int rh = (node->right != nullptr) ? node->right->height : 0; // Высота правого поддерева
    node->height = 1 + max(lh, rh); 
}

int getHeight(Node* node) {
    if (node == nullptr) return 0; //  чтобы меньеш в условиии писать
    return node->height;
}

// Правый поворот
Node* rightRotate(Node* y) {
    Node* x = y->left;   
    Node* T2 = x->right; 

    x->right = y;  // y становится правым ребёнком x
    y->left = T2;  // Поддерево T2 становится левым ребёнком y
    // Выполняем поворот
    updateHeight(y);
    updateHeight(x);

    return x; 
}

//Левый поворот
Node* leftRotate(Node* x) {
    Node* y = x->right;  
    Node* T2 = y->left; 

    y->left = x;   
    x->right = T2; 

    updateHeight(x);
    updateHeight(y);

    return y;
}


int GetBalance(Node* node) { // кэф балансироки 
    if (node == nullptr) return 0;
    int lh = (node->left != nullptr) ? node->left->height : 0;
    int rh = (node->right != nullptr) ? node->right->height : 0;
    return lh - rh;
}


Node* Insert(Node* node, int key) {
    if (node == nullptr) return new Node(key); // если узел пуст — создаём новый

    if (key < node->key) {
        node->left = Insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = Insert(node->right, key);
    }
    else {
        return node;
    }

    updateHeight(node);
    if (node == nullptr) return node;

    // Вычисляем баланс
    int balance = GetBalance(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR 
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR 
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* MinValNode(Node* node) {
    Node* cur = node;
    while (cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}

Node* DeleteNode(Node* node, int key) {
    if (node == nullptr) return node;
    
    if (key < node->key) {
        node->left = DeleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = DeleteNode(node->right, key);
    }
    else {// найден
        if (node->left == nullptr || node->right == nullptr) { // Узел имеет 0 или 1 приемника
            Node* temp = (node->left != nullptr) ? node->left : node->right;
            if (temp == nullptr) { // нет 
                delete node;
                node = nullptr;
            }
            else { // есть 1
                *node = *temp;
                delete temp;
            }    
        }
        else {
            Node* temp = MinValNode(node->right);
            node->key = temp->key;
            node->right = DeleteNode(node->right, temp->key);
        }
    }
    if (node == nullptr) return node;
    updateHeight(node);
    int balance = GetBalance(node);
    if (balance > 1 && GetBalance(node->left) >= 0) {// LL
        return rightRotate(node);
    }
    if (balance > 1 && GetBalance(node->left) < 0) {//LR
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && GetBalance(node->right) <= 0) {// RR
        return leftRotate(node);
    }
    if (balance < -1 && GetBalance(node->right) > 0) {// RL
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


//обход в ширину
void BFS(Node* node) {
    if (node == nullptr) {
        cout << "Дерево пустое\n";
        return;
    }

    Queue q;
    q.push(node);

    while (!q.IsEmpty()) {
        Node* cur = q.pop();
        cout << cur->key << " ";
        if (cur->left != nullptr) q.push(cur->left);
        if (cur->right != nullptr) q.push(cur->right);
    }
    cout << '\n';
}

Node* Search(Node* node, int key, int& steps) {
    Node* cur = node;
    steps = 0;
    while(cur != nullptr) {
        steps++;
        if (key == cur->key) return cur;
        else if (key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return nullptr;
}

void findMinMaxLeaf(Node* node, int& minh, int& maxh, int& minVal, int& maxVal) {
    if (node == nullptr) {
        minh = maxh = 0;
        return;
    }

    Queue q;
    q.push(node);
    int level = 1;
    int nodesOnLevel = 1;
    int nextLevelCount = 0;

    minh = INT_MAX;
    maxh = 0;

    while (!q.IsEmpty()) {
        Node* cur = q.pop();
        nodesOnLevel--;

        if (cur->left == nullptr && cur->right == nullptr) {// если лист
            if (level < minh) {
                minh = level;
                minVal = cur->key;
            }
            if (level > maxh) {
                maxh = level;
                maxVal = cur->key;
            }
        }

        if (cur->left) {
            q.push(cur->left);
            nextLevelCount++;
        }
        if (cur->right) {
            q.push(cur->right);
            nextLevelCount++;
        }

        if (nodesOnLevel == 0) {
            nodesOnLevel = nextLevelCount;
            nextLevelCount = 0;
            level++;
        }
    }
}


void AutoBalanse(Node*& node) {
    if (node == nullptr) return;

    int minh, maxh, minVal, maxVal;
    while (true) {
        findMinMaxLeaf(node, minh, maxh, minVal, maxVal);
        cout << "minh = " << minh << " (лист " << minVal << "), "
            << "maxh = " << maxh << " (лист " << maxVal << ")\n";

        if (minh == maxh) {
            cout << "Условие minh = maxh выполнено!\n";
            break;
        }

        cout << "Удаляем нижний лист " << maxVal << "...\n";
        node = DeleteNode(node, maxVal);
        BFS(node);
        cout << "\n";

    }
}


void BFSWithLevels(Node* root) {
    if (!root) {
        cout << "Дерево пустое\n";
        return;
    }

    Queue q;
    q.push(root);
    int level = 1;
    int nodesOnLevel = 1;
    int nextLevelCount = 0;

    cout << "Уровень " << level << ": ";
    while (!q.IsEmpty()) {
        Node* cur = q.pop();
        cout << cur->key << " ";
        nodesOnLevel--;

        if (cur->left) { q.push(cur->left); nextLevelCount++; }
        if (cur->right) { q.push(cur->right); nextLevelCount++; }

        if (nodesOnLevel == 0) {
            if (!q.IsEmpty()) {
                level++;
                cout << "\nУровень " << level << ": ";
            }
            nodesOnLevel = nextLevelCount;
            nextLevelCount = 0;
        }
    }
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    Node* node = nullptr;
    int choice, key;

    while (true) {
        cout << "МЕНЮ\n";
        cout << "1. Добавить элемент\n";
        cout << "2. Удалить элемент\n";
        cout << "3. Найти элемент\n";
        cout << "4. Вывести дерево (BFS с уровнями)\n";
        cout << "5. Авто-балансировка (удаление нижних листьев до равенства уровней)\n";
        cout << "6. Выйти\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Введите значение для добавления: ";
            cin >> key;
            node = Insert(node, key);
            cout << "Элемент " << key << " добавлен.\n";
        }
        else if (choice == 2) {
            cout << "Введите значение для удаления: ";
            cin >> key;
            node = DeleteNode(node, key);
            cout << "Элемент " << key << " удалён \n";
        }
        else if (choice == 3) {
            cout << "Введите значение для поиска: ";
            cin >> key;
            int steps;
            Node* found = Search(node, key, steps);
            if (found)
                cout << "Элемент найден за " << steps << " шаг(ов).\n";
            else
                cout << "Элемент не найден.\n";
        }
        else if (choice == 4) {
            cout << "Дерево (BFS с уровнями):\n";
            BFSWithLevels(node);
        }
        else if (choice == 5) {
            cout << "Авто-балансировка дерева...\n";
            AutoBalanse(node);
        }
        else if (choice == 6) {
            cout << "Дерево\n";
            BFS(node);
        }
        else if (choice == 7) {
            cout << "Выход из программы.\n";
            break;
        }
        else {
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }

    return 0;
}