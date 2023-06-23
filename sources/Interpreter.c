#include "include/Interpreter.h"

void insertCommandFunc(Interpreter* interpreter)
{
    long key;
    nodeValueType value;

    if (sscanf(interpreter->buffer, "%*s %ld " NODE_VALUE_TYPE_STDIO_FORMAT "\n", &key, &value) != 2) {
        fprintf(stderr, "ERROR: INSERT command requires 2 arguments\n");
    } else {
        insert(&(interpreter->tree), key, value);
    }
}

void eraseCommandFunc(Interpreter* interpreter)
{
    long key;

    if (!sscanf(interpreter->buffer, "%*s %ld\n", &key)) {
        fprintf(stderr, "ERROR: ERASE command requires 1 argument\n");
    } else {
        erase(&(interpreter->tree), key);
    }
}

void exitCommandFunc(Interpreter* interpreter)
{
    interpreter->endFlag = 1;
}

void prettyPrintCommandFunc(Interpreter* interpreter)
{
    prettyPrintTreeToFile(interpreter->tree, 0, 0, interpreter->fileOut);
}

void inorderTraversalCommandFunc(Interpreter* interpreter)
{
    printInorderTraversalToFile(interpreter->tree, interpreter->fileOut);
    fprintf(interpreter->fileOut, "\n");
}

void cleanTreeCommandFunc(Interpreter* interpreter)
{
    deleteTree(interpreter->tree);
    interpreter->tree = NULL;
}

void helpCommandFunc(Interpreter* interpreter)
{
    fprintf(interpreter->fileOut, "Every command is case-insensitive. Commands list:\n");
    for (size_t i = 0; i < commandsCount; i++) {
        fprintf(interpreter->fileOut, "%lu. %s Aliases:\n", i + 1, commands[i].description);

        for (size_t j = 0; commands[i].aliases[j]; j++) {
            fprintf(interpreter->fileOut, "\t- \"%s\"\n", commands[i].aliases[j]);
        }

        fprintf(interpreter->fileOut, "Example: %s\n", commands[i].example);
    }
}

Interpreter* makeCustomInterpreter(FILE* fileIn, FILE* fileOut)
{
    if (!fileIn || !fileOut) {
        fprintf(stderr, "ERROR: unable to open input/output file correctly\n");
        return NULL;
    }

    Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
    interpreter->fileIn = fileIn;
    interpreter->fileOut = fileOut;
    interpreter->tree = NULL;
    interpreter->endFlag = 0;

    return interpreter;
}

Interpreter* makeFileInterpreter(const char* fileIn, const char* fileOut)
{
    return makeCustomInterpreter(fopen(fileIn, "r"), fopen(fileOut, "w"));
}

Interpreter* makeConsoleInterpreter()
{
    return makeCustomInterpreter(stdin, stdout);
}

void interpret(Interpreter* interpreter)
{
    int commandFoundFlag = 0;

    char command[sizeof(interpreter->buffer)];
    command[0] = 0;

    sscanf(interpreter->buffer, "%s", command);

    /* Пропускаем комментарий или пустую строку */
    if (!command[0] || command[0] == COMMENT_SYMBOL) {
        return;
    }

    /* Пытаемся найти подходящую команду */
    for (size_t i = 0; i < commandsCount && !commandFoundFlag; i++) {
        for (size_t j = 0; commands[i].aliases[j]; j++) {
            if (!strcasecmp(command, commands[i].aliases[j])) {
                commands[i].commandFuncPtr(interpreter);
                commandFoundFlag = 1;
                break;
            }
        }
    }

    if (!commandFoundFlag) {
        fprintf(stderr, "ERROR: unknown command: \"%s\". Type \"" HELP_MESSAGE_ALIAS "\" for help\n", command);
    }
}

void start(Interpreter* interpreter)
{
    if (interpreter->fileIn == stdin && interpreter->fileOut == stdout) {
        fprintf(interpreter->fileOut, PROMPT);
    }
    /* Продолжаем, пока не введена команда завершения или пока не закончился файл */
    while (!interpreter->endFlag && fgets(interpreter->buffer, sizeof(interpreter->buffer), interpreter->fileIn)) {
        interpret(interpreter);

        if (interpreter->fileIn == stdin && interpreter->fileOut == stdout) {
            fprintf(interpreter->fileOut, PROMPT);
        }
    }

    deleteTree(interpreter->tree);

    if (interpreter->fileIn != stdin)
        fclose(interpreter->fileIn);
    if (interpreter->fileOut != stdout)
        fclose(interpreter->fileOut);

    free(interpreter);
}
