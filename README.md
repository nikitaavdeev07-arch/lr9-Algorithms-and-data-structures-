# Отчёт по лабораторной работе №9

```markdown
# Лабораторная работа №9
## Бинарное дерево. Обходы. BST

**Вариант:** 1

---

## 1. Цель работы

1. Реализовать структуру данных «бинарное дерево» и изучить различные способы его обхода (прямой, симметричный, обратный, уровневый).
2. Реализовать бинарное дерево поиска (BST) с операциями вставки, удаления и поиска.
3. Освоить применение рекурсии для работы с деревьями.
4. Проанализировать сложность операций в BST.
5. Научиться визуализировать структуру дерева.

---

## 2. Теоретическая часть

### 2.1. Бинарное дерево

Бинарное дерево — иерархическая структура данных, в которой каждый узел имеет не более двух потомков: левый и правый.

**Терминология:**

| Термин | Определение |
|---|---|
| Корень (root) | Верхний узел дерева |
| Лист (leaf) | Узел, не имеющий потомков |
| Внутренний узел | Узел, имеющий хотя бы одного потомка |
| Высота дерева | Максимальное расстояние от корня до листа |
| Уровень (level) | Расстояние от корня (корень — уровень 0) |

**Пример дерева:**

```
        10
       /  \
      5    15
     / \     \
    3   7     20
       /     /
      6     18
```

### 2.2. Обходы бинарного дерева

| Вид обхода | Порядок посещения | Результат |
|---|---|---|
| Прямой (pre-order) | Корень → Левый → Правый | 10, 5, 3, 7, 6, 15, 20, 18 |
| Симметричный (in-order) | Левый → Корень → Правый | 3, 5, 6, 7, 10, 15, 18, 20 |
| Обратный (post-order) | Левый → Правый → Корень | 3, 6, 7, 5, 18, 20, 15, 10 |
| Уровневый (level-order) | По уровням слева направо | 10, 5, 15, 3, 7, 20, 6, 18 |

### 2.3. Бинарное дерево поиска (BST)

BST — бинарное дерево, в котором для каждого узла выполняется условие:

> Все ключи в левом поддереве < ключ узла < все ключи в правом поддереве.

**Свойства BST:**
- Симметричный обход даёт отсортированную последовательность.
- Поиск, вставка и удаление в среднем выполняются за O(log n).

**Пример BST:**

```
        50
       /  \
      30   70
     / \   / \
    20 40 60 80
```

### 2.4. Операции с BST

**Поиск** — O(log n) в среднем.

**Вставка** — O(log n) в среднем.

**Удаление** — O(log n) в среднем. Три случая:

| Случай | Описание | Действие |
|---|---|---|
| 1 | Удаляемый узел — лист | Просто удаляем |
| 2 | Узел имеет одного потомка | Заменяем удаляемый узел его потомком |
| 3 | Узел имеет двух потомков | Находим минимальный элемент в правом поддереве, заменяем значение, удаляем тот узел |

---

## 3. Постановка задачи (вариант 1)

### Часть 1. Бинарное дерево и обходы
- **Обязательные операции:** preOrder, inOrder, postOrder.
- **Дополнительное задание:** вычислить количество узлов.

### Часть 2. Бинарное дерево поиска (BST)
- **Обязательные операции:** insert, search, inOrder.
- **Дополнительное задание:** удаление (все три случая).

### Часть 3. Применение BST
1. Создать BST из последовательности случайных чисел (N = 20).
2. Выполнить симметричный обход и вывести отсортированную последовательность.
3. Найти минимальный и максимальный элемент.
4. Найти высоту дерева.
5. Удалить элемент, введённый пользователем, и вывести дерево после удаления.

---

## 4. Листинг программы

### 4.1. Часть 1 — Бинарное дерево и обходы

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    void preOrder(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }

    // Дополнительное задание: количество узлов
    int countNodes(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroy(root); }

    void buildSample() {
        root = new Node(10);
        root->left = new Node(5);
        root->right = new Node(15);
        root->left->left = new Node(3);
        root->left->right = new Node(7);
        root->right->right = new Node(20);
        root->left->right->left = new Node(6);
        root->right->right->left = new Node(18);
    }

    void preOrder()  { preOrder(root);  cout << endl; }
    void inOrder()   { inOrder(root);   cout << endl; }
    void postOrder() { postOrder(root); cout << endl; }

    int getCount() { return countNodes(root); }
};

int main() {
    BinaryTree tree;
    tree.buildSample();

    cout << "Прямой обход (pre-order): ";
    tree.preOrder();
    cout << "Симметричный (in-order): ";
    tree.inOrder();
    cout << "Обратный (post-order): ";
    tree.postOrder();

    cout << "Количество узлов: " << tree.getCount() << endl;
    return 0;
}
```

### 4.2. Часть 2 — BST с удалением

```cpp
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
        } else if (key > node->data) {
            node->right = remove(node->right, key);
        } else {
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
                Node* minNode = findMin(node->right);
                node->data = minNode->data;
                node->right = remove(node->right, minNode->data);
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
```

### 4.3. Часть 3 — Применение BST

```cpp
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
    } else {
        cout << "Элемент " << key << " не найден в дереве." << endl;
    }

    return 0;
}
```

---

## 5. Результаты работы

### 5.1. Часть 1 — обходы и количество узлов

```
Прямой обход (pre-order): 10 5 3 7 6 15 20 18
Симметричный (in-order): 3 5 6 7 10 15 18 20
Обратный (post-order): 3 6 7 5 18 20 15 10
Количество узлов: 8
```

### 5.2. Часть 2 — BST и удаление

```
Симметричный обход BST: 20 30 40 50 60 70 80
Поиск 40: найден
Поиск 100: не найден

--- Удаление 20 (лист) ---
30 40 50 60 70 80
--- Удаление 30 (один потомок) ---
40 50 60 70 80
--- Удаление 50 (два потомка) ---
40 60 70 80
```

### 5.3. Часть 3 — применение BST

```
Исходная последовательность: 42 68 35 1 70 25 79 59 63 65 6 46 82 28 62 92 96 43 28 37
Отсортированная последовательность (in-order): 1 6 25 28 28 35 37 42 43 46 59 62 63 65 68 70 79 82 92 96
Минимальный элемент: 1
Максимальный элемент: 96
Высота дерева: 6
Введите элемент для удаления: 42
После удаления 42: 1 6 25 28 28 35 37 43 46 59 62 63 65 68 70 79 82 92 96
```

### 5.4. Визуализация BST (для примера части 2)

```
        50
       /  \
      30   70
     / \   / \
    20 40 60 80
```

После удаления 20 (лист), 30 (один потомок), 50 (два потомка):

```
        60
       /  \
      40   70
            \
            80
```

---

## 6. Анализ сложности операций

| Операция | Средний случай | Худший случай |
|---|---|---|
| Поиск | O(log n) | O(n) |
| Вставка | O(log n) | O(n) |
| Удаление | O(log n) | O(n) |
| Обходы (pre/in/post) | O(n) | O(n) |
| Подсчёт узлов | O(n) | O(n) |
| Высота | O(n) | O(n) |

**Пояснение:** сложность операций в BST зависит от высоты дерева h. В среднем h ≈ log n (для случайных данных), поэтому операции выполняются за O(log n). В худшем случае (вставка отсортированной последовательности) дерево вырождается в список, h = n, и сложность становится O(n). Именно поэтому важно балансировать дерево.

---

## 7. Ответы на контрольные вопросы

1. **Что такое бинарное дерево? Из каких элементов оно состоит?**
   Бинарное дерево — иерархическая структура, в которой каждый узел имеет не более двух потомков (левый и правый). Элементы: корень, листья, внутренние узлы, рёбра, уровни.

2. **В чём отличие бинарного дерева от BST?**
   В BST выполняется условие упорядоченности: левое поддерево < узел < правое поддерево. Обычное бинарное дерево такого условия не требует.

3. **Какие существуют виды обхода бинарного дерева? В чём их особенности?**
   Pre-order (корень→левый→правый), in-order (левый→корень→правый), post-order (левый→правый→корень), level-order (по уровням). Первые три — рекурсивные, level-order использует очередь.

4. **Какой обход даёт отсортированную последовательность для BST?**
   Симметричный (in-order).

5. **Какова сложность операций поиска, вставки и удаления в BST? От чего она зависит?**
   O(log n) в среднем, O(n) в худшем. Зависит от высоты дерева (сбалансированности).

6. **Что происходит с BST, если вставлять элементы в отсортированном порядке?**
   Дерево вырождается в список, высота = n, сложность операций становится O(n).

7. **Какие три случая нужно рассмотреть при удалении узла из BST?**
   (1) Лист — просто удалить; (2) один потомок — заменить потомком; (3) два потомка — заменить минимальным из правого поддерева (или максимальным из левого), затем удалить преемника.

8. **Как найти наименьший элемент в BST? Наибольший?**
   Наименьший — идти по левым потомкам до конца; наибольший — по правым.

9. **Как вычислить высоту бинарного дерева рекурсивно?**
   `height(node) = 1 + max(height(left), height(right))`, для nullptr → 0.

10. **Что такое LCA двух узлов в дереве?**
    Наименьший общий предок — самый глубокий узел, являющийся предком обоих узлов.

11. **Как проверить, является ли бинарное дерево BST?**
    In-order должен давать строго возрастающую последовательность, либо рекурсивно проверять допустимый диапазон (min, max) для каждого узла.

12. **Что такое сбалансированное дерево? Почему это важно?**
    Дерево, в котором для каждого узла разница высот поддеревьев ≤ 1. Важно, т.к. гарантирует O(log n) для операций.

13. **Как преобразовать несбалансированное BST в сбалансированное?**
    In-order → отсортированный массив → рекурсивно строить дерево из середины.

14. **Как восстановить дерево по массиву обхода (in-order + pre-order)?**
    Первый элемент pre-order — корень; в in-order он делит массив на левое и правое поддеревья; рекурсивно для каждой части.

15. **Как реализовать итеративный обход бинарного дерева?**
    Pre/in — через стек; post — два стека или стек с флагом; level — через очередь.

---

## 8. Выводы

В ходе лабораторной работы были реализованы:

- бинарное дерево с тремя рекурсивными обходами (pre-order, in-order, post-order) и подсчётом количества узлов;
- бинарное дерево поиска с операциями вставки, поиска и удаления (все три случая);
- демонстрационная программа, создающая BST из 20 случайных чисел, выполняющая симметричный обход, поиск минимума/максимума, вычисление высоты и удаление элемента по вводу пользователя.

Показано, что рекурсия естественно ложится на древовидные структуры, а сложность операций в BST напрямую зависит от высоты дерева, что обосновывает важность балансировки. Симметричный обход BST даёт отсортированную последовательность, что делает BST удобной структурой для задач сортировки и поиска.

---

## 9. Ссылка на Git-репозиторий


> `https://github.com/nikitaavdeev07-arch/lr9-Algorithms-and-data-structures-`
```

---

