#include "include/Interpreter.h"

void insertCommandFunc(const Command *command, Interpreter *interpreter)
{
    long key;
    nodeValueType value;
    fscanf(interpreter->fileIn, "%ld " NODE_VALUE_TYPE_STDIO_FORMAT "\n", &key, &value);

    insert(&(interpreter->tree), key, value);
}

void eraseCommandFunc(const Command *command, Interpreter *interpreter)
{
    long key;
    fscanf(interpreter->fileIn, "%ld\n", &key);

    erase(&(interpreter->tree), key);
}

void exitCommandFunc(const Command *command, Interpreter *interpreter)
{
    deleteTree(interpreter->tree);
    free(interpreter);
}

void prettyPrintCommandFunc(const Command *command, Interpreter *interpreter)
{
    prettyPrintTree(interpreter->tree, 0, 0);
}

void inorderTraversalCommandFunc(const Command *command, Interpreter *interpreter)
{
    printInorderTraversal(interpreter->tree);
    fprintf(interpreter->fileOut, "\n");
}

void interpret(Interpreter **interpreterPtr)
{
    Interpreter* interpreter = *interpreterPtr;

    int commandFoundFlag;
    char* command;

    while (interpreter) {
        commandFoundFlag = 0;
        fscanf(interpreter->fileIn, "%s", command);

        for (size_t i = 0; i < commandsCount && !commandFoundFlag; i++) {
            for (size_t j = 0; commands[i].aliases[j]; j++) {
                if (!strcasecmp(command, commands[i].aliases[j])) {
                    commands[i].commandFuncPtr(commands + i, interpreter);
                    commandFoundFlag = 1;
                    break;
                }
            }
        }

        if (!commandFoundFlag) {
            fprintf(interpreter->fileOut, "ERROR: unknown command: \"%s\"\n", command);
        }
    }
}

Interpreter *makeCustomInterpreter(FILE *fileIn, FILE *fileOut)
{
    Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
    interpreter->fileIn = fileIn;
    interpreter->fileOut = fileOut;
    interpreter->tree = NULL;

    return interpreter;
}

Interpreter *makeFileInterpreter(const char *fileIn, const char *fileOut)
{
    return makeCustomInterpreter(fopen(fileIn, "r"), fopen(fileOut, "w"));
}

Interpreter *makeConsoleInterpreter()
{
    return makeCustomInterpreter(stdin, stdout);
}

void start(Interpreter **interpreter)
{
    interpret(interpreter);
}
