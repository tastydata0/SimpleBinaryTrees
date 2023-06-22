#include "include/Tree.h"

Node* makeNode(const long key, const nodeValueType value)
{
    Node* node = (Node*)malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert(Node** tree, long key, nodeValueType value)
{
    if (*tree == NULL) {
        *tree = makeNode(key, value);
        return;
    }

    /* Если такой ключ уже есть в дереве */
    if ((*tree)->key == key) {
        return;
    }

    if ((*tree)->key < key) {
        insert(&((*tree)->right), key, value);
    } else {
        insert(&((*tree)->left), key, value);
    }
}

Node* leftLeaf(Node* tree)
{
    while (tree->left)
        tree = tree->left;

    return tree;
}

void erase(Node** tree, const long key)
{
    if (*tree == NULL) {
        return;
    } else if ((*tree)->key == key) {
        /* Удаляемый узел найден */

        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            /* Если это лист */
            free(*tree);
            *tree = NULL;
        } else if ((*tree)->left && (*tree)->right) {
            /* Если у узла есть 2 дочерних узла, то находим ближайший больший элемент-лист, который встает на место удаляемого узла. */
            Node* closest = leftLeaf((*tree)->right);
            const long key = closest->key;
            const nodeValueType value = closest->value;
            erase(tree, key);
            (*tree)->key = key;
            (*tree)->value = value;
        } else {
            /* Если есть единственный дочерний узел */
            Node* child = (*tree)->left ? (*tree)->left : (*tree)->right;
            free(*tree);
            *tree = child;
        }
    } else if ((*tree)->key < key) {
        erase(&(*tree)->right, key);
    } else {
        erase(&(*tree)->left, key);
    }
}

void prettyPrintTreeToFile(Node* tree, int depth, int isLastChild, FILE* fileOut)
{
    if (tree == NULL) {
        return;
    }

    for (int i = 0; i < depth - 1; i++) {
        fprintf(fileOut, NODE_PREFIX_TOP_LEVEL);
    }

    if (depth) {
        if (isLastChild) {
            fprintf(fileOut, NODE_PREFIX_LAST);
        } else {
            fprintf(fileOut, NODE_PREFIX);
        }
    }

    fprintf(fileOut, "%ld(" NODE_VALUE_TYPE_STDIO_FORMAT ")\n", tree->key, tree->value);
    prettyPrintTreeToFile(tree->left, depth + 1, 0, fileOut);
    prettyPrintTreeToFile(tree->right, depth + 1, 1, fileOut);
}

void prettyPrintTree(Node* tree, int depth, int isLastChild)
{
    prettyPrintTreeToFile(tree, depth, isLastChild, stdout);
}

void deleteTree(Node* tree)
{
    if (!tree)
        return;

    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}

void printInorderTraversalToFile(Node* tree, FILE* fileOut)
{
    if (!tree)
        return;

    printInorderTraversalToFile(tree->left, fileOut);
    fprintf(fileOut, "%ld(" NODE_VALUE_TYPE_STDIO_FORMAT ") ", tree->key, tree->value);
    printInorderTraversalToFile(tree->right, fileOut);
}

void printInorderTraversal(Node* tree)
{
    printInorderTraversalToFile(tree, stdout);
}
