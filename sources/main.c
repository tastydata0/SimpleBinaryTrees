#include "include/Interpreter.h"

int main()
{
    Interpreter* consoleInterpreter = makeConsoleInterpreter();
    Interpreter* fileInterpreter = makeFileInterpreter("testFileIn.txt", "testFileOut.txt");
    Interpreter* fromFileToConsoleInterpreter = makeCustomInterpreter(fopen("testFileIn.txt", "r"), stdout);

    if (fileInterpreter) {
        start(fileInterpreter);
    }

    if (consoleInterpreter) {
        start(consoleInterpreter);
    }

    if (fromFileToConsoleInterpreter) {
        printf("\n * fromFileToConsoleInterpreter started\n\n");
        start(fromFileToConsoleInterpreter);
    }

    printf("\n * creating interpreterWithIncorrectFile...\n\n");
    Interpreter* interpreterWithIncorrectFile = makeCustomInterpreter(fopen("fileDoesNotExist.error", "r"), stdout);
}
