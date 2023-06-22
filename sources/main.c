#include "include/Interpreter.h"

int main()
{
//    struct Node* tree = NULL;

//    long nodeKeys[] = { 40, 30, 50, 25, 26, 24, 27, 35, 28, 29, 31, 32, 33, 36, 37, 60, 60, 60, 43 };

//    for (int i = 0; i < sizeof(nodeKeys) / sizeof(nodeKeys[0]); i++)
//        insert(&tree, nodeKeys[i], rand() % 100);

//    erase(&tree, 27);
//    erase(&tree, 33);
//    erase(&tree, 40);

//    prettyPrintTree(tree, 0, 1);

//    printInorderTraversal(tree);
//    printf("\n");

//    deleteTree(tree);

    Interpreter* interpreter = makeConsoleInterpreter();

    start(&interpreter);

    free(interpreter);
}
