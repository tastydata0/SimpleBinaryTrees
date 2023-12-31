#ifndef TREE_H
#define TREE_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/// Значения для функции prettyPrintTree
#define NODE_PREFIX "├── "
#define NODE_PREFIX_LAST "└── "
#define NODE_PREFIX_TOP_LEVEL "│   "

///
/// \brief nodeValueType - тип данных, используемый в качестве значения узла дерева
///
typedef long nodeValueType;

/// Формат для функций из stdio.h для значения узла
#define NODE_VALUE_TYPE_STDIO_FORMAT "%ld"

///
/// \brief Node - структура узла дерева. Имеет ключ, значение и указатели на дочерние элементы
///
typedef struct Node {
    long key;
    nodeValueType value;

    struct Node* left;
    struct Node* right;
} Node;

///
/// \brief makeNode - функция создания узла. Создаёт узел при помощи динамического выделения памяти
/// \param key - ключ, который будет иметь создаваемый узел
/// \param value - значение, которое будет иметь создаваемый узел
/// \return Указатель на созданный узел
///
Node* makeNode(const long key, const nodeValueType value);

///
/// \brief insert - функция вставки узла в дерево с сохранением сортировки
/// \details Вызывает функцию makeNode с переданными key и value
/// \param tree - указатель на указатель на дерево (необходимо для модификации указателя на дерево)
/// \param key - ключ, который будет иметь создаваемый узел
/// \param value - значение, которое будет иметь создаваемый узел
///
void insert(Node** tree, long key, nodeValueType value);

///
/// \brief leftLeaf - функция получения крайнего левого узла (левого листа) в дереве
/// \param tree - дерево для поиска искомого элемента
/// \return Левый лист в дереве
///
Node* leftLeaf(Node* tree);

///
/// \brief erase - функция удаления элемента из дерева по ключу
/// \details Вызывает free() с удаляемым элементом, т.е. он должен быть создан динамически
/// \param tree - указатель на указатель на дерево (необходимо для модификации указателя на дерево)
/// \param key - ключ удаляемого узла
///
void erase(Node** tree, const long key);

///
/// \brief prettyPrintTreeToFile - функция наглядного вывода дерева в файловый поток (подобно команде tree в linux)
/// \param tree - указатель на дерево для вывода
/// \param depth - глубина рекурсии, значение для внутреннего использования. При вызове извне следует передавать 0
/// \param isLastChild - является ли текущий узел последним дочерним элементом. Значение для внутреннего использования. При вызове извне следует передавать 0
/// \param fileOut - валидный файловый поток
///
void prettyPrintTreeToFile(Node* tree, int depth, int isLastChild, FILE* fileOut);

///
/// \brief prettyPrintTree - функция наглядного вывода дерева в консоль (подобно команде tree в linux)
/// \param tree - указатель на дерево для вывода
/// \param depth - глубина рекурсии, значение для внутреннего использования. При вызове извне следует передавать 0
/// \param isLastChild - является ли текущий узел последним дочерним элементом. Значение для внутреннего использования. При вызове извне следует передавать 0
///
void prettyPrintTree(Node* tree, int depth, int isLastChild);

///
/// \brief printInorderTraversalToFile - функция вывода в файловый поток обхода дерева в порядке возрастания ключа
/// \param tree - указатель на дерево для обхода
/// \param fileOut - валидный файловый поток
///
void printInorderTraversalToFile(Node* tree, FILE* fileOut);

///
/// \brief printInorderTraversal - функция вывода в консоль обхода дерева в порядке возрастания ключа
/// \param tree - указатель на дерево для обхода
///
void printInorderTraversal(Node* tree);

///
/// \brief deleteTree - функция рекурсивного удаления дерева при помощи free()
/// \param tree - указатель на дерево для удаления
///
void deleteTree(Node* tree);

#endif // TREE_H
