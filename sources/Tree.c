#include "include/Tree.h"

struct Node* makeNode(const long key, const nodeValueType value)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert(struct Node** tree, long key, nodeValueType value)
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

struct Node* leftLeaf(struct Node* tree)
{
    while (tree->left)
        tree = tree->left;

    return tree;
}

void erase(struct Node** tree, const long key)
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
            struct Node* closest = leftLeaf((*tree)->right);
            const long key = closest->key;
            const nodeValueType value = closest->value;
            erase(tree, key);
            (*tree)->key = key;
            (*tree)->value = value;
        } else {
            /* Если есть единственный дочерний узел */
            struct Node* child = (*tree)->left ? (*tree)->left : (*tree)->right;
            free(*tree);
            *tree = child;
        }
    } else if ((*tree)->key < key) {
        erase(&(*tree)->right, key);
    } else {
        erase(&(*tree)->left, key);
    }
}

void prettyPrintTree(struct Node* tree, int depth, int isLastChild)
{
    if (tree == NULL) {
        return;
    }

    for (int i = 0; i < depth - 1; i++) {
        printf(NODE_PREFIX_TOP_LEVEL);
    }

    if (depth) {
        if (isLastChild) {
            printf(NODE_PREFIX_LAST);
        } else {
            printf(NODE_PREFIX);
        }
    }

    printf("%ld(%ld)\n", tree->key, tree->value);
    prettyPrintTree(tree->left, depth + 1, 0);
    prettyPrintTree(tree->right, depth + 1, 1);
}

void deleteTree(struct Node* tree)
{
    if (!tree)
        return;

    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}

void printInorderTraversal(struct Node* tree)
{
    if (!tree)
        return;

    printInorderTraversal(tree->left);
    printf("%ld(%ld) ", tree->key, tree->value);
    printInorderTraversal(tree->right);
}
