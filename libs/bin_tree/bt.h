#ifndef INC_BT_H
#define INC_BT_H
#include "stdlib.h"

struct El {
    int data;
    struct El* rSon;
    struct El* lSon;

};

struct Bt {
    struct El** root;
    int num;
};

typedef struct El El;
typedef struct Bt Bt;

// Инициализирует корень бинарного дерева bin_tree
void InitBT(Bt *bin_tree);

// Удаляет бинарное дерево bin_tree
void DeleteBT(Bt *bin_tree);

// Вставляет в бинарное дерево bin_tree элемент el
int InsertElBT(Bt *bin_tree, int el);

// Удаляет из бинарного дерева bin_tree элемент el и возвращает 1, если он там есть, иначе возвращает 0
int DeleteElBT(Bt *bin_tree, int el);

#endif INC_BT_H
