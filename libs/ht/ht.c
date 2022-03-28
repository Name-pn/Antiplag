#include "ht.h"

// Инициализирует хеш-таблицу
void InitHT(Ht *ht, int size) {
    ht->size = size;
    ht->mas = calloc(sizeof(Bt), size);
    ht->num_el = 0;


    for (int i = 0; i < size; ++i) {
        InitBT(&(ht->mas[i]));
    }
}

// Удаляет хеш-таблицу ht размера size
void DeleteHT(Ht *ht, int size) {
    for (int i = 0; i < size; ++i) {
        DeleteBT(&(ht->mas[i]));
    }
    free(ht->mas);
}

// Возвращает значение хеш-функции по хеш-таблице ht от num_to_hash
int hash(Ht *ht, int num_to_hash) {
    return abs((num_to_hash*MULTIPLIED+SUMMAND)) % ht->size;
}

// Вставляет элемент el в хеш-таблицу ht
void InsertElHT(Ht *ht, int el) {
    int hh = hash(ht, el);
    ht->num_el += InsertElBT(&(ht->mas[hh]), el);
}

// Удаляет элемент el из таблицы ht
void DeleteElHT(Ht *ht, int el) {
    int hh = hash(ht, el);
    ht->num_el -= DeleteElBT(&(ht->mas[hh]), el);
}