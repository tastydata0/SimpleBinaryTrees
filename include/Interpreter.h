#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <string.h>
#include "include/Tree.h"

typedef struct {
    FILE* fileIn;
    FILE* fileOut;

    Node* tree;
} Interpreter;

typedef struct Command {
    const char* description;
    const char* aliases[17];

    void (*commandFuncPtr)(const struct Command*, Interpreter*);
} Command;

void insertCommandFunc(const Command* command, Interpreter* interpreter);

void eraseCommandFunc(const Command* command, Interpreter* interpreter);

void exitCommandFunc(const Command* command, Interpreter* interpreter);

void prettyPrintCommandFunc(const Command* command, Interpreter* interpreter);

void inorderTraversalCommandFunc(const Command* command, Interpreter* interpreter);

static const Command commands[] = {
    // Description                                  Aliases                                                  Command function
    {"Insert custom node to a tree",                {"+", "ADD", "INSERT", NULL},                            &insertCommandFunc},
    {"Erase node from tree by key",                 {"-", "ERASE", "DELETE", "REMOVE", NULL},                &eraseCommandFunc},
    {"Exit program deleting the tree if needed",    {"E", "ESC", "EXIT", "STOP", NULL},                      &exitCommandFunc},
    {"Pretty-print a tree",                         {"PP", "TREE", "PRETTY_PRINT", NULL},                    &prettyPrintCommandFunc},
    {"Print in-order traversal of a tree",          {"P", "TRAVERSAL", "INORDER_TRAVERSAL", "PRINT", NULL},  &inorderTraversalCommandFunc}
};

static const size_t commandsCount = sizeof(commands) / sizeof(commands[0]);

Interpreter* makeCustomInterpreter(FILE* fileIn, FILE* fileOut);

Interpreter* makeFileInterpreter(const char* fileIn, const char* fileOut);

Interpreter* makeConsoleInterpreter();

void interpret(Interpreter** interpreterPtr);

void start(Interpreter** interpreter);

#endif // INTERPRETER_H
