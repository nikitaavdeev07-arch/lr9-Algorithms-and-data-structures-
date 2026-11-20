// Project2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == nullptr) return new Node(key);
        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        // если key == node->data — дубликат, ничего не делаем
        return node;
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->data == key) return node;
        if (key < node->data) return search(node->left, key);
        return search(node->right, key);
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    // Удаление — все три случая
    Node* remove(Node* node, int key) {
        if (node == nullptr) return nullptr;

        if (key < node->data) {
            node->left = remove(node->left, key);
        }
        else if (key > node->data) {
            node->right = remove(node->right, key);
        }
        else {
            // Случай 1: лист
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Случай 2: один потомок (правый)
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Случай 2: один потомок (левый)
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Случай 3: два потомка
            else {
                Node* minNode = findMin(node->right);      // минимальный в правом поддереве
                node->data = minNode->data;                // заменяем значение
                node->right = remove(node->right, minNode->data); // удаляем преемника
            }
        }
        return node;
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int key) { root = insert(root, key); }
    bool search(int key) { return search(root, key) != nullptr; }
    void remove(int key) { root = remove(root, key); }
    void print() { inOrder(root); cout << endl; }
};

int main() {
    setlocale(LC_ALL, "RU_ru");
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Симметричный обход BST: ";
    tree.print();

    cout << "Поиск 40: " << (tree.search(40) ? "найден" : "не найден") << endl;
    cout << "Поиск 100: " << (tree.search(100) ? "найден" : "не найден") << endl;

    // Проверка всех трёх случаев удаления
    cout << "\n--- Удаление 20 (лист) ---" << endl;
    tree.remove(20);
    tree.print();

    cout << "--- Удаление 30 (один потомок) ---" << endl;
    tree.remove(30);
    tree.print();

    cout << "--- Удаление 50 (два потомка) ---" << endl;
    tree.remove(50);
    tree.print();

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
