// Project3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
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
        if (key < node->data) node->left = insert(node->left, key);
        else if (key > node->data) node->right = insert(node->right, key);
        return node;
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->data == key) return node;
        return key < node->data ? search(node->left, key) : search(node->right, key);
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* findMax(Node* node) {
        while (node && node->right) node = node->right;
        return node;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) return nullptr;
        if (key < node->data) node->left = remove(node->left, key);
        else if (key > node->data) node->right = remove(node->right, key);
        else {
            if (!node->left && !node->right) { delete node; return nullptr; }
            else if (!node->left) { Node* t = node->right; delete node; return t; }
            else if (!node->right) { Node* t = node->left; delete node; return t; }
            else {
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
            }
        }
        return node;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int key) { root = insert(root, key); }
    void remove(int key) { root = remove(root, key); }
    bool search(int key) { return search(root, key) != nullptr; }
    void print() { inOrder(root); cout << endl; }
    int getHeight() { return height(root); }
    int getMin() { return findMin(root)->data; }
    int getMax() { return findMax(root)->data; }
};

int main() {
    setlocale(LC_ALL, "RU_ru");
    srand(time(0));
    BST tree;

    cout << "Исходная последовательность: ";
    for (int i = 0; i < 20; ++i) {
        int x = rand() % 100;
        cout << x << " ";
        tree.insert(x);
    }
    cout << endl;

    cout << "Отсортированная последовательность (in-order): ";
    tree.print();

    cout << "Минимальный элемент: " << tree.getMin() << endl;
    cout << "Максимальный элемент: " << tree.getMax() << endl;
    cout << "Высота дерева: " << tree.getHeight() << endl;

    int key;
    cout << "Введите элемент для удаления: ";
    cin >> key;

    if (tree.search(key)) {
        tree.remove(key);
        cout << "После удаления " << key << ": ";
        tree.print();
    }
    else {
        cout << "Элемент " << key << " не найден в дереве." << endl;
    }

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
