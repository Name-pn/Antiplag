#ifndef INC_HT_H
#define INC_HT_H

#include "../bin_tree/bt.h"

#define MULTIPLIED 263
#define SUMMAND 1

struct Ht {
    Bt *mas;
    int size;
    int num_el;
};

typedef struct Ht Ht;

// Инициализирует хеш-таблицу ht размера size
void InitHT(Ht *ht, int size);

// Удаляет хеш-таблицу ht размера size
void DeleteHT(Ht *ht, int size);

// Вставляет элемент el в хеш-таблицу ht
void InsertElHT(Ht *ht, int el);

// Удаляет элемент el из таблицы ht
void DeleteElHT(Ht *ht, int el);

#endif //INC_HT_H
