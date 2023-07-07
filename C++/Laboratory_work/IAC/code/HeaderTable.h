#include <iostream>
#include <queue>

using namespace std;

typedef struct List* ptrel;

typedef struct List { // Cмотреть лаб.раб. №5
    float data;     // поле данных
    char key;      // ключ
    ptrel left;   // левый потомок
    ptrel right;  // правый потомок
};

typedef List Table;

int comparison(void* keyOne, void* keyTwo);

typedef char T_Key; // Определить тип ключа 
typedef int (*func)(void*, void*); /* Сравнивает ключи элементов таблицы, адреса которых находятся в параметрах a и b. Возвращает –1, если ключ элемента по адресу a меньше ключа элемента по адресу b, 0 — если ключи равны и +1 — если ключ элемента по адресу a больше ключа элемента по адресу b */

// Нужна для удаления веришны из дерева
void deleteDeepestNode(Table* root, Table* deleting_node);

// Нужно для поиска нужного ключа с данными и дальнешей передачи для удаления этой вершины
Table* deleteNode(Table* root, char key, float& data);

void outputTable(Table* tree);

/* Исключение элемен-та. Возвращает 1 , если элемент с ключем Key был в таблице, иначе — 0 */
int GetTable(Table* T, void** E, T_Key Key, func f);

void InitTable(Table* T, unsigned SizeMem, unsigned SizeEl);

/* Включение элемента в таблицу. */
int PutTable(T_Key key, float data, Table* T, func f);

/* Возвращает 1 , если таблица пуста, иначе — 0 */
inline int EmptyTable(Table* T);

/* Чтение элемента. Возвращает 1 , если элемент с ключем Key есть в таблице, иначе — 0 */
int ReadTable(Table* T, float& E, T_Key Key, func f);

/* Изменение элемен-та. Возвращает 1 , если элемент с ключем Key есть в таблице, иначе — 0 */
int WriteTable(Table* T, float E, T_Key Key, func f);

//Удаление таблицы из динамической памяти 
void DoneTable(Table* T);
