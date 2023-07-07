#include <iostream>
#include <queue>
#include"HeaderTable.h"

using namespace std;

int comparison(void* keyOne, void* keyTwo) { // Если одинаковые 1, иначе 0
    return (char)keyOne == (char)keyTwo ? 1 : 0;
}

void deleteDeepestNode(Table* root, Table* deleting_node) {
    queue<Table*> nodes;
    nodes.push(root);
    Table* temp;
    while (!nodes.empty()) {
        temp = nodes.front();
        nodes.pop();
        if (temp == deleting_node) {
            temp = NULL;
            delete (deleting_node);
            return;
        }
        if (temp->right) {
            if (temp->right == deleting_node) {
                temp->right = NULL;

                delete deleting_node;
                return;
            }
            else {
                nodes.push(temp->right);
            }
        }
        if (temp->left) {
            if (temp->left == deleting_node) {
                temp->left = NULL;
                delete deleting_node;
                return;
            }
            else {
                nodes.push(temp->left);
            }
        }
    }
}

// Нужно для поиска нужного ключа с данными и дальнешей передачи для удаления этой вершины
Table* deleteNode(Table* root, char key, float& data) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->key == key)
            return NULL;
        else 
            return root;
    }

    queue<Table*> nodes;
    nodes.push(root);
    Table* temp = NULL;
    Table* key_node = NULL;
    while (!nodes.empty()) {
        temp = nodes.front();
        nodes.pop();
        if (temp->key == key) {
            key_node = temp;
            data = temp->data;
        }
        if (temp->left) {
            nodes.push(temp->left);
        }
        if (temp->right) {
            nodes.push(temp->right);
        }
    }

    if (key_node != NULL) {
        char deepest_node_data = temp->key;
        float data_temp = temp->data;
        deleteDeepestNode(root, temp);
        key_node->key = deepest_node_data;
        key_node->data = data_temp;
    }
    return root;
}

void outputTable(Table* tree) { //Вывод таблицы
    if (tree != NULL) {      //Пока не встретится пустой узел
        outputTable(tree->left);  //Рекурсивная функция вывода левого поддерева
        cout << "Key: " << (char)tree->key << " Data: " << tree->data << " " << endl; //Отображаем корень дерева
        outputTable(tree->right); //Рекурсивная функция вывода правого поддерева
    }
}

/* Исключение элемен-та. Возвращает 1 , если элемент с ключем Key был в таблице, иначе — 0 */
int GetTable(Table* T, void** data, T_Key Key, func f) {
    Table* time = T;
    float number = NULL;

    deleteNode(T, Key, number);
    *data = &number;
    if (number != NULL)
        return 1;
    return 0;
}

void InitTable(Table* T, unsigned SizeMem, unsigned SizeEl) {
    T->data = 0;
    T->key = '0';
    T->left = NULL;
    T->right = NULL;
}

/* Включение элемента в таблицу. Возвращает 1 ,
если элемент включен в таблицу, иначе — 0
(если в таблице уже есть элемент с заданным ключем или нехватает памяти)  */
int PutTable(T_Key key, float data, Table* T,func f) { // ✓
    Table* node_one = T, * node_two = T;

    while (node_two != NULL) {
        node_one = node_two;
        if (!f((void*)key, (void*)T->key)) {
            if (key < node_two->key)
                node_two = node_two->left;
            else if (key > node_two->key)
                node_two = node_two->right;
            else
                return 0;
        }
    }

    node_two = new Table();
    if (node_two == NULL)
        return 0;
    node_two->left = node_two->right = NULL;
    node_two->data = data;
    node_two->key = key;
    if (T == NULL)
        T = node_two;
    else if (key < node_one->key)
        node_one->left = node_two;
    else
        node_one->right = node_two;
    return 1;
}

/* Возвращает 1 , если таблица пуста, иначе — 0 */
inline int EmptyTable(Table* T) { // ✓
    return T == NULL ? 1 : 0;
}

/* Чтение элемента. Возвращает 1 , если элемент с ключем Key есть в таблице, иначе — 0 */
int ReadTable(Table* T, float& data, T_Key Key, func f) { // ✓
    if (T == NULL)
        return 0;
    else if (Key < T->key)
        return ReadTable(T->left, data, Key, f);
    else if (Key > T->key)
        return ReadTable(T->right, data, Key, f);
    else {
        data = T->data;
        return 1;
    }
    return 0;
}

/* Изменение элемен-та. Возвращает 1 , если элемент с ключем Key есть в таблице, иначе — 0 */
int WriteTable(Table* T, float data, T_Key Key, func f) { // ✓
    if (T == NULL)
        return 0;
    else if (Key < T->key)
        return WriteTable(T->left, data, Key, f);
    else if (Key > T->key)
        return WriteTable(T->right, data, Key, f);
    else {
        T->data = data;
        return 1;
    }
    return 0;
}

//Удаление таблицы из динамической памяти 
void DoneTable(Table* T) {
    delete T;
}


