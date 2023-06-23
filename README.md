# SimpleBinaryTrees

SimpleBinaryTrees - программа для работы с бинарными деревьями. Каждый узел дерева имеет ключ и значение.

Поддерживаемые функции:
* Добавление в дерево с сохранениеи порядка сортировки
* Удаление элемента по ключу
* Наглядный вывод в консоль (подобно команде `tree` в linux)
* Обход дерева в порядке возрастания элементов

## Пример использования:
```c
#include "include/Tree.h"

int main()
{
    struct Node* tree = NULL;

    long nodeKeys[] = { 40, 30, 50, 25, 26, 24, 27, 35, 28, 29, 31, 32, 33, 36, 37, 60, 60, 60, 43 };

    for (int i = 0; i < sizeof(nodeKeys) / sizeof(nodeKeys[0]); i++)
        insert(&tree, nodeKeys[i], rand() % 100);

    prettyPrintTree(tree, 0, 1);

    erase(&tree, 27);
    erase(&tree, 33);
    erase(&tree, 40);

    prettyPrintTree(tree, 0, 1);

    printInorderTraversal(tree);
    printf("\n");

    deleteTree(tree);
}
```
Stdout:
```
43(72)
├── 30(86)
│   ├── 25(15)
│   │   ├── 24(35)
│   │   └── 26(93)
│   │   │   └── 28(49)
│   │   │   │   └── 29(21)
│   └── 35(92)
│   │   ├── 31(62)
│   │   │   └── 32(27)
│   │   └── 36(59)
│   │   │   └── 37(63)
└── 50(77)
│   └── 60(26)
24(35) 25(15) 26(93) 28(49) 29(21) 30(86) 31(62) 32(27) 35(92) 36(59) 37(63) 43(72) 50(77) 60(26)
```
## Интерактивный режим
Есть возможность работы с деревьями в интерактивном режиме, а также посредством написания простых скриптов. Функции для этого хранятся в `"Interpreter.h"`. Перед запуском интерактивного режима, нужно создать интерпретатор, передав туда поток ввода и вывода. Это могут быть файлы или стандартные потоки ввода-вывода. Есть также функции-обёртки, передающие потоки и открывающие файлы за вас. Пример создания интерпретаторов:
```cpp
Interpreter* consoleInterpreter = makeConsoleInterpreter(); // Консольный
Interpreter* fileInterpreter = makeFileInterpreter("testFileIn.txt", "testFileOut.txt"); // Файловый
Interpreter* fromFileToConsoleInterpreter = makeCustomInterpreter(fopen("testFileIn.txt", "r"), stdout); // Гибридный
```
Полный код создания интерпретаторов и работы с ними:
```cpp
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
```
Для вывода списка команд напишите `?` или 'help'. Программа отобразит команды, содержащиеся в `commands[]` в `Interpreter.h`:
```
 > ?
Every command is case-insensitive. Commands list:
1. Insert node to a tree. Args: key and value. Aliases:
	- "+"
	- "ADD"
	- "INSERT"
	- "MK"
	- "MKNODE"
Example: add 7 14
2. Erase node from tree by key. Arg: key. Aliases:
	- "-"
	- "ERASE"
	- "DELETE"
	- "REMOVE"
Example: erase 7
3. Exit program deleting the tree if needed. Aliases:
	- "E"
	- "ESC"
	- "EXIT"
	- "STOP"
Example: e (or <CTRL+D> as EOF)
4. Pretty-print a tree. Aliases:
	- "PP"
	- "TREE"
	- "PRETTY_PRINT"
Example: pp
5. Print in-order traversal of a tree. Aliases:
	- "P"
	- "LS"
	- "INORDER_TRAVERSAL"
	- "PRINT"
Example: ls
6. Clean tree. Aliases:
	- "C"
	- "CLEAR"
	- "CLEAN"
Example: c
7. Print this help message. Aliases:
	- "?"
	- "HELP"
	- "COMMANDS"
Example: help
 >
```

Пример работы в консольном режиме:
```
 > add 5 9
 > add 3 8
 > add 19 9
 > add 18 7
 > add 0 2
 > print
0(2) 3(8) 5(9) 18(7) 19(9)
 > tree
5(9)
├── 3(8)
│   ├── 0(2)
└── 19(9)
│   ├── 18(7)
 > erase 5
 > tree
18(7)
├── 3(8)
│   ├── 0(2)
└── 19(9)
 > exit
```
Пример работы скрипта, переданного в интерпретатор (строки с префиксом `#` игнорируются интерпретатором):

`testFileIn.txt`:
```
# Add some values
add 9 0
add 8 13
add 1237 12372
add 19 3
add 20 4

# Normal print
p

# Pretty print
pp

# Erase some values
erase 9
erase 20

# Normal print
p

# Pretty print
pp

# End can be explicitly specified, but program will exit correctly on EOF
# exit

```
`testFileOut.txt`:
```
8(13) 9(0) 19(3) 20(4) 1237(12372) 
9(0)
├── 8(13)
└── 1237(12372)
│   ├── 19(3)
│   │   └── 20(4)
8(13) 19(3) 1237(12372) 
19(3)
├── 8(13)
└── 1237(12372)
```
