#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boardgame.h"

void all_vivod(baza* a) {
    if (a->count == 0) {
        printf("Список игр пуст\n");
        return;
    }
    
    printf("\n=== СПИСОК НАСТОЛЬНЫХ ИГР (%d шт.) ===\n", a->count);
    for (int i = 0; i < a->count; i++) {
        printf("Игра #%d: %s | %s | %d игроков | %d+ | %.2f руб. | %d шт.\n",
               i + 1, a->games[i].name, a->games[i].genre,
               a->games[i].players, a->games[i].age,
               a->games[i].price, a->games[i].stock);
    }
}

void add(baza* a, int f) {
    if (a->count >= a->capacity) {
        int new_capacity = (a->capacity == 0) ? 5 : a->capacity * 2;
        boardgame* new_games = realloc(a->games, new_capacity * sizeof(boardgame));
        if (new_games == NULL) {
            printf("Ошибка выделения памяти!\n");
            return;
        }
        a->games = new_games;
        a->capacity = new_capacity;
    }
    
    if (f) {
        printf("Введите название игры: ");
        scanf("%s", a->games[a->count].name);
        
        printf("Введите жанр: ");
        scanf("%s", a->games[a->count].genre);
        
        printf("Введите количество игроков: ");
        scanf("%d", &a->games[a->count].players);
        
        printf("Введите минимальный возраст: ");
        scanf("%d", &a->games[a->count].age);
        
        printf("Введите цену: ");
        scanf("%f", &a->games[a->count].price);
        
        printf("Введите количество на складе: ");
        scanf("%d", &a->games[a->count].stock);
    }
    
    a->count++;
    printf("Игра добавлена!\n");
}

void delite(baza* a, char* name) {
    int found = 0;
    for (int i = 0; i < a->count; i++) {
        if (strcmp(a->games[i].name, name) == 0) {
            for (int j = i; j < a->count - 1; j++) {
                a->games[j] = a->games[j + 1];
            }
            a->count--;
            found = 1;
            printf("Игра '%s' удалена\n", name);
            break;
        }
    }
    
    if (!found) {
        printf("Игра '%s' не найдена\n", name);
    }
}

void search(baza* a, char* name, char* genre) {
    int found = 0;
    printf("\n=== РЕЗУЛЬТАТЫ ПОИСКА ===\n");
    
    for (int i = 0; i < a->count; i++) {
        int match_name = (strlen(name) == 0) || (strcmp(a->games[i].name, name) == 0);
        int match_genre = (strlen(genre) == 0) || (strcmp(a->games[i].genre, genre) == 0);
        
        if (match_name && match_genre) {
            printf("Найдено: %s | %s | %d игроков | %d+ | %.2f руб. | %d шт.\n",
                   a->games[i].name, a->games[i].genre,
                   a->games[i].players, a->games[i].age,
                   a->games[i].price, a->games[i].stock);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Игры не найдены\n");
    }
}

void redact(baza* a, char* name) {
    for (int i = 0; i < a->count; i++) {
        if (strcmp(a->games[i].name, name) == 0) {
            printf("Редактирование игры '%s':\n", name);
            
            printf("Новое название (старое: %s): ", a->games[i].name);
            scanf("%s", a->games[i].name);
            
            printf("Новый жанр (старый: %s): ", a->games[i].genre);
            scanf("%s", a->games[i].genre);
            
            printf("Новое количество игроков (старое: %d): ", a->games[i].players);
            scanf("%d", &a->games[i].players);
            
            printf("Новый минимальный возраст (старый: %d+): ", a->games[i].age);
            scanf("%d", &a->games[i].age);
            
            printf("Новая цена (старая: %.2f): ", a->games[i].price);
            scanf("%f", &a->games[i].price);
            
            printf("Новое количество на складе (старое: %d): ", a->games[i].stock);
            scanf("%d", &a->games[i].stock);
            
            printf("Игра отредактирована!\n");
            return;
        }
    }
    printf("Игра '%s' не найдена\n", name);
}

void save(const char* filename, baza* a) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return;
    }
    
    for (int i = 0; i < a->count; i++) {
        fprintf(file, "%s %s %d %d %.2f %d\n",
                a->games[i].name,
                a->games[i].genre,
                a->games[i].players,
                a->games[i].age,
                a->games[i].price,
                a->games[i].stock);
    }
    
    fclose(file);
    printf("Данные сохранены в файл '%s'\n", filename);
}

void load(char* filename, baza* a) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл '%s' не найден. Будет создан новый.\n", filename);
        return;
    }
    
    char name[50], genre[50];
    int players, age, stock;
    float price;
    
    while (fscanf(file, "%s %s %d %d %f %d",
                  name, genre, &players, &age, &price, &stock) == 6) {
        add(a, 0);
       
        strcpy(a->games[a->count - 1].name, name);
        strcpy(a->games[a->count - 1].genre, genre);
        a->games[a->count - 1].players = players;
        a->games[a->count - 1].age = age;
        a->games[a->count - 1].price = price;
        a->games[a->count - 1].stock = stock;
    }
    
    fclose(file);
    printf("Загружено %d игр из файла '%s'\n", a->count, filename);
}

void free_baza(baza* a) {
    if (a->games != NULL) {
        free(a->games);
        a->games = NULL;
    }
    a->count = 0;
    a->capacity = 0;
}
