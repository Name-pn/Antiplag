#include "bt.h"

// Инициализирует корень бинарного дерева bin_tree
void InitBT(Bt *bin_tree) {
    bin_tree->root = (El**)calloc(sizeof(El*), 1);
    bin_tree->num = 0;
}

// Освобождает память занятую вершиной bin_tree
void delete_top(El **bin_tree) {
    free(*bin_tree);
    *bin_tree = NULL;
}

// Обходит дерево bin_tree в обратном порядке при обходе вызывает функцию f над каждой вершиной
void reverse_order_pass_sup(El **bin_tree, void f(El**)) {
    if ((*bin_tree)->lSon != NULL)
        reverse_order_pass_sup(&((*bin_tree)->lSon), f);
    if ((*bin_tree)->rSon != NULL)
        reverse_order_pass_sup(&((*bin_tree)->rSon), f);
    f(bin_tree);
}

// Начинает обход дерева bin_tree в обратном порядке при обходе вызывает функцию f над каждой вершиной
void reverse_order_pass(Bt *bin_tree, void f(El **)) {
    if (*(bin_tree->root) != NULL) {
        reverse_order_pass_sup(bin_tree->root, f);
    }
    f(bin_tree->root);
}

// Удаляет бинарное дерево bin_tree
void DeleteBT(Bt *bin_tree) {
    reverse_order_pass(bin_tree, delete_top);
}

// Вставляет в бинарное дерево bin_tree элемент k и возвращает 1, если k в дереве нет, иначе возвращает 0
int InsertElBT(Bt *bin_tree, int k) {
    if (*(bin_tree->root) == NULL) {
        *(bin_tree->root) = calloc(sizeof(El), 1);
        (**(bin_tree->root)).data = k;
    } else {
        struct El **pointer = bin_tree->root;
        while (!(((*pointer)->lSon == NULL && (*pointer)->data > k) || ((*pointer)->rSon == NULL && (*pointer)->data <= k))) {
            if ((*pointer)->data > k)
                pointer = &((*pointer)->lSon);
            else
                pointer = &((*pointer)->rSon);
        }
        if ((*pointer)->lSon == NULL && (*pointer)->data > k) {
            (*pointer)->lSon = calloc(sizeof(El), 1);
            pointer = &((*pointer)->lSon);
            (*pointer)->data = k;
        }
        if ((*pointer)->rSon == NULL && (*pointer)->data <= k) {
            (*pointer)->rSon = calloc(sizeof(El), 1);
            pointer = &((*pointer)->rSon);
            (*pointer)->data = k;
        }
    }
    bin_tree->num++;
    return 1;
}

El** find(Bt *bin_tree, int k) {
    struct El **pointer = bin_tree->root;
    while ((*pointer) != NULL && (*pointer)->data != k) {
        if ((*pointer)->data > k)
            pointer = &((*pointer)->lSon);
        else
            pointer = &((*pointer)->rSon);
    }
    return pointer;
}

enum code_top_status{LEAF = 0, LEFT_SON = 1, RIGHT_SON = 2, TWO_SON = 3};

// Удаляет элемент bin_tree по указателю pointer способом случая левого потомка
void delete_with_lSon(Bt *bin_tree, struct El ** pointer) {
    struct El *pointer_lSon  = (*pointer)->lSon; // Сохранение адреса сына
    free(*pointer); // Удаление старого элемента
    (*pointer) = pointer_lSon; // Запись адреса сына
}

// Удаляет элемент bin_tree по указателю pointer способом случая правого потомка
void delete_with_rSon(Bt *bin_tree, struct El ** pointer) {
    struct El *pointer_rSon  = (*pointer)->rSon; // Сохранение адреса сына
    free(*pointer); // Удаление старого элемента
    (*pointer) = pointer_rSon; // Запись адреса сына

}

// Удаляет элемент bin_tree по указателю pointer способом случая двух потомков
void delete_with_two_sons(Bt *bin_tree, struct El ** pointer_change_el) {
    struct El **pointer_alternate_el;

    struct El *lPointer, *rPointer;
    struct El *buf = ((*pointer_change_el)->lSon); // Для хранения этого адреса нужна отдельная п-ная
    pointer_alternate_el = &buf;

    if ((*pointer_alternate_el)->rSon != NULL) {
        while ((*pointer_alternate_el)->rSon != NULL || (*pointer_alternate_el)->lSon != NULL) {
            while ((*pointer_alternate_el)->rSon != NULL) {
                pointer_alternate_el = &((*pointer_alternate_el)->rSon);
            }
            while ((*pointer_alternate_el)->lSon != NULL && (*pointer_alternate_el)->rSon == NULL) {
                pointer_alternate_el = &((*pointer_alternate_el)->lSon);
            }
        }

        lPointer = (*pointer_change_el)->lSon;
        rPointer = (*pointer_change_el)->rSon;
        free(*pointer_change_el);
        (*pointer_alternate_el)->lSon = lPointer;
        (*pointer_alternate_el)->rSon = rPointer;
        (*pointer_change_el) = (*pointer_alternate_el);

        (*pointer_alternate_el) = NULL;
    } else {
        rPointer = (*pointer_change_el)->rSon;
        free(*pointer_change_el);
        (*pointer_change_el) = (*pointer_alternate_el);
        (*pointer_change_el)->rSon = rPointer;
    }
}

// Удаляет из бинарного дерева bin_tree элемент El и возвращает 1, если он там есть, иначе возвращает 0
int DeleteElBT(Bt *bin_tree, int k) {
    struct El **pointer = find(bin_tree, k);

    if (*pointer != NULL) {
        int top_status = ((*pointer)->lSon != NULL) + 2* ((*pointer)->rSon != NULL);
        switch (top_status) {
            case LEAF: {
                delete_top(pointer);
                break;
            }
            case LEFT_SON: {
                delete_with_lSon(bin_tree, pointer);
                break;
            }
            case RIGHT_SON: {
                delete_with_rSon(bin_tree, pointer);
                break;
            }
            case TWO_SON: {
                delete_with_two_sons(bin_tree, pointer);
                break;
            }
        }
        bin_tree->num--;
        return 1;
    }
    return 0;
}