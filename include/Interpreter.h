#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <string.h>
#include "include/Tree.h"

/// Если на интерпретатор подать строку с этим символом в начале, она будет воспринята как комментарий
#define COMMENT_SYMBOL '#'

/// Нужен для вывода этого алиаса в сообщение о некорректной команде
#define HELP_MESSAGE_ALIAS "HELP"

/// Приглашение терминала в интерактивном режиме
#define PROMPT " > "

/// Структура интерпретатора, содержащая файловые потоки ввода-вывода, буфер ввода команды, дерево для работы и флаг завершения работы
typedef struct {
    FILE* fileIn;
    FILE* fileOut;

    char buffer[128];

    Node* tree;

    int endFlag;
} Interpreter;

/// Структура команды интерпретатора, содержащая описание, алиасы (максимум их можно сделать 16, последним всегда должен быть NULL)
/// Содержит также указатель на функцию, которая вызовется при вводе соответствующей команды и пример использования команды.
typedef struct Command {
    const char* description;
    const char* aliases[17];

    void (*commandFuncPtr)(Interpreter*);

    const char* example;
} Command;

///
/// \brief insertCommandFunc - функция команды добавления узла в дерево
/// \param interpreter - интерпретатор с валидными файловыми потоками и буфером ввода
///
void insertCommandFunc(Interpreter* interpreter);

///
/// \brief eraseCommandFunc - функция команды удаления узла из дерева
/// \param interpreter - интерпретатор с валидными файловыми потоками и буфером ввода
///
void eraseCommandFunc(Interpreter* interpreter);

///
/// \brief exitCommandFunc - функция завершения работы интерпретатора. Устанавливает флаг завершения, ничего не удаляя
/// \param interpreter - интерпретатор с валидными файловыми потоками
///
void exitCommandFunc(Interpreter* interpreter);

///
/// \brief prettyPrintCommandFunc - функция команды наглядного вывода дерева
/// \param interpreter - интерпретатор с валидными файловыми потоками
///
void prettyPrintCommandFunc(Interpreter* interpreter);

///
/// \brief inorderTraversalCommandFunc - функция команды вывода обхода дерева в порядке возрастания ключа
/// \param interpreter - интерпретатор с валидными файловыми потоками
///
void inorderTraversalCommandFunc(Interpreter* interpreter);

///
/// \brief cleanTreeCommandFunc - функция команды очищения дерева
/// \param interpreter - интерпретатор с валидными файловыми потоками
///
void cleanTreeCommandFunc(Interpreter* interpreter);

///
/// \brief cleanTreeCommandFunc - функция команды вывода сообщения с синтаксисом команд
/// \param interpreter - интерпретатор с валидными файловыми потоками
///
void helpCommandFunc(Interpreter* interpreter);

/// Список команд, вдохновлённый конфиг-файлом dwm.
/// Позволяет легко задавать собственные команды, распределяя их код на отдельные функции (см. struct Command).
/// На основе этого массива выводится информация для help.
static const Command commands[] = {

    /* Description                                   Aliases                                          Command function              Example */

    {"Insert node to a tree. Args: key and value.",  {"+", "ADD", "INSERT", "MK", "MKNODE", NULL},    &insertCommandFunc,           "add 7 14"},
    {"Erase node from tree by key. Arg: key.",       {"-", "ERASE", "DELETE", "REMOVE", NULL},        &eraseCommandFunc,            "erase 7"},
    {"Exit program deleting the tree if needed.",    {"E", "ESC", "EXIT", "STOP", NULL},              &exitCommandFunc,             "e (or <CTRL+D> as EOF)"},
    {"Pretty-print a tree.",                         {"PP", "TREE", "PRETTY_PRINT", NULL},            &prettyPrintCommandFunc,      "pp"},
    {"Print in-order traversal of a tree.",          {"P", "LS", "INORDER_TRAVERSAL", "PRINT", NULL}, &inorderTraversalCommandFunc, "ls"},
    {"Clean tree.",                                  {"C", "CLEAR", "CLEAN", NULL},                   &cleanTreeCommandFunc,        "c"},
    {"Print this help message.",                     {"?", HELP_MESSAGE_ALIAS, "COMMANDS", NULL},     &helpCommandFunc,             "help"}
};

/// Количество команд. Число необходимо для работы некоторых функций, работающих с командами
static const size_t commandsCount = sizeof(commands) / sizeof(commands[0]);

///
/// \brief makeCustomInterpreter - базовая функция создания интерпретатора
/// \param fileIn - файловый поток ввода
/// \param fileOut - файловый поток вывода
/// \return Interpreter*, если файлы открыты успешно, иначе NULL. В случае возврата NULL, в stderr также будет выведено сообщение об ошибке
///
Interpreter* makeCustomInterpreter(FILE* fileIn, FILE* fileOut);

///
/// \brief makeFileInterpreter - функция-обертка для makeCustomInterpreter
/// \param fileIn - имя файла для чтения. Файл обязан существовать
/// \param fileOut - имя файла для вывода
/// \return Interpreter*, если файлы открыты успешно, иначе NULL
///
Interpreter* makeFileInterpreter(const char* fileIn, const char* fileOut);

///
/// \brief makeConsoleInterpreter - функция-обертка для makeCustomInterpreter
/// \return Interpreter* - указатель на интерпретатор
///
Interpreter* makeConsoleInterpreter();

///
/// \brief interpret - функция интерптетатора, читающая из его буфера строчку и интерпретирующая его в соответствии со списком команд (см. commands)
/// \param interpreter - указатель на интерпретатор
///
void interpret(Interpreter* interpreter);

///
/// \brief start - функция для запуска жизненного цикла интерпретатора.
/// \details После завершения работы интерпретатора, очищается его дерево, если оно не пустое, закрываются файлы, если это не stdin и stdout и удаляется сам интерпретатор.
/// \param interpreter - указатель на интерпретатор
///
void start(Interpreter* interpreter);


#endif // INTERPRETER_H
