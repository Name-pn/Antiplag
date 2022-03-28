#include "libs/bin_tree/bt.h"
#include "libs/ht/ht.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>

// Параметры хеш-таблицы
#define HT_SIZE 100000

// Параметры РК хеш-функции
#define P 263
#define Q 4194304
#define SENTENCE_SIZE 15

// Параметры строк чтения файла
#define MAX_FILE_SIZE 100000
#define MAX_ROW_SIZE 1000

// Имена файлов
char f_pattern_name[] = "pattern.txt";
char f_checked_name[] = "checked.txt";

// Считывает текстовое содержимое физического файла f_name и записывает его в res
void fgets_txt(char* f_name, char *res) {
    res[0] = 0;
    char buf_row[MAX_FILE_SIZE];

    FILE* f = fopen(f_name, "r");
    if (f == NULL)
        fprintf(stderr, "Ошибка открытия файла %s\n", f_name);
    while (!feof(f)) {

        fgets(buf_row, MAX_ROW_SIZE, f);
        strcat(res, buf_row);
    }

    fclose(f);
}

// Возвращает хеш следующий подстроки по коээфициенту сдвига d,
// уходящему символу old_ch, новому символу строки new_ch и
// хешу предыдущей подстроки old_h
int rehash(int old_ch, int new_ch, int old_h, int d) {
    return ((( old_h - old_ch * d ) * P ) + new_ch) % Q;
}

// Заполняет хеш-таблицу ht хешами подстрок длины m строки s длины n
void download_kr(Ht *ht, char* s, int n, int m) {
    int hs, d, i;

    d = 1;
    for (i = 1; i < m; i++)
        d = (d * P) % Q;

    hs = 0;
    for (i = 0; i < m; i++) {
        hs = ((hs * P) + s[i]) % Q;
    }

    for (i = m; i < n; i++) {

        /*
        `\color{codegreen}Если добавить в условие memcmp(\&s[i - m], subs, m) == 0,`
        `\color{codegreen}то коллизиции будут исключены, но потеряем время и смысл РК`
        `\color{codegreen}memcmp - функция лексикографического сравнения массивов`
        */
        InsertElHT(ht, hs);
        hs = rehash(s[i - m], s[i], hs, d);
    }
    InsertElHT(ht, hs);
}

// Удаляет из хеш-таблицы ht хеши подстрок длины m строки s длины n
void delete_kr(Ht *ht, char* s, int n, int m) {
    int hs, d, i;

    d = 1;
    for (i = 1; i < m; i++)
        d = (d * P) % Q;

    hs = 0;
    for (i = 0; i < m; i++) {
        hs = ((hs * P) + s[i]) % Q;
    }

    for (i = m; i < n; i++) {

        /*
        `\color{codegreen}Если добавить в условие memcmp(\&s[i - m], subs, m) == 0,`
        `\color{codegreen}то коллизиции будут исключены, но потеряем время и смысл РК`
        `\color{codegreen}memcmp - функция лексикографического сравнения массивов`
        */
        DeleteElHT(ht, hs);
        hs = rehash(s[i - m], s[i], hs, d);
    }
    DeleteElHT(ht, hs);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    printf("Вас приветствует программа определения процента плагиата\n");
    printf("Запущена проверка файла %s на плагиат из %s\n", f_checked_name, f_pattern_name);

    Ht sentences;
    InitHT(&sentences, HT_SIZE);

    char pattern_txt[MAX_FILE_SIZE];
    char checked_txt[MAX_FILE_SIZE];

    fgets_txt(f_pattern_name, pattern_txt);
    fgets_txt(f_checked_name, checked_txt);

    download_kr(&sentences, pattern_txt, strlen(pattern_txt), SENTENCE_SIZE);
    int old_num = sentences.num_el;

    delete_kr(&sentences, checked_txt, strlen(checked_txt), SENTENCE_SIZE);
    int new_num = sentences.num_el;

    double coincidence = old_num - new_num;
    double res = coincidence / old_num * 100;

    printf("Процент совпадения: %i%%", (int)res);

    return 0;
}
