#include "boardgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_store(GameStore* store) {
    store->count = 0;
    store->capacity = 5; 
    store->games = (BoardGame*)malloc(store->capacity * sizeof(BoardGame));
    if (store->games == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
}

void free_store(GameStore* store) {
    if (store->games != NULL) {
        free(store->games);
        store->games = NULL;
    }
    store->count = 0;
    store->capacity = 0;
}

void resize_store(GameStore* store) {
    int new_capacity = store->capacity * 2;
    BoardGame* new_games = (BoardGame*)realloc(store->games, new_capacity * sizeof(BoardGame));
    
    if (new_games == NULL) {
        printf("Ошибка перевыделения памяти!\n");
        return;
    }
    
    store->games = new_games;
    store->capacity = new_capacity;
    printf("Массив увеличен до %d элементов\n", new_capacity);
}

void add_game(GameStore* store) {
    if (store->count >= store->capacity) {
        resize_store(store);
    }
    
    printf("\n--- Добавление новой игры ---\n");
  
    printf("Название: ");
    scanf("%s", store->games[store->count].name);
    
    printf("Жанр: ");
    scanf("%s", store->games[store->count].genre);
    
    printf("Минимальное кол-во игроков: ");
    scanf("%d", &store->games[store->count].min_players);
    
    printf("Максимальное кол-во игроков: ");
    scanf("%d", &store->games[store->count].max_players);
    
    printf("Цена: ");
    scanf("%f", &store->games[store->count].price);
    
    printf("Количество на складе: ");
    scanf("%d", &store->games[store->count].in_stock);
    
    store->games[store->count].id = store->count + 1;
    
    store->count++;
    printf("Игра добавлена! Всего игр: %d\n", store->count);
}

void show_all(GameStore* store) {
    printf("\n=== КАТАЛОГ ИГР (%d шт.) ===\n", store->count);
    
    if (store->count == 0) {
        printf("Игр нет.\n");
        return;
    }
    
    for (int i = 0; i < store->count; i++) {
        BoardGame* g = &store->games[i];
        printf("\nID: %d\n", g->id);
        printf("  Название: %s\n", g->name);
        printf("  Жанр: %s\n", g->genre);
        printf("  Игроков: %d-%d\n", g->min_players, g->max_players);
        printf("  Цена: %.2f руб.\n", g->price);
        printf("  В наличии: %d шт.\n", g->in_stock);
        printf("------------------------\n");
    }
}

void search_by_name(GameStore* store) {
    char name[MAX_NAME];
    printf("Введите название для поиска: ");
    scanf("%s", name);
    
    printf("\n--- Результаты поиска ---\n");
    int found = 0;
    
    for (int i = 0; i < store->count; i++) {
     
        if (strstr(store->games[i].name, name) != NULL) {
            BoardGame* g = &store->games[i];
            printf("\nID: %d | %s | %s | %d-%d игроков | %.2f руб. | %d шт.\n",
                   g->id, g->name, g->genre, g->min_players, g->max_players, g->price, g->in_stock);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Игры с названием '%s' не найдены.\n", name);
    }
}

void search_by_genre(GameStore* store) {
    char genre[MAX_GENRE];
    printf("Введите жанр для поиска: ");
    scanf("%s", genre);
    
    printf("\n--- Игры жанра '%s' ---\n", genre);
    int found = 0;
    
    for (int i = 0; i < store->count; i++) {
        if (strcmp(store->games[i].genre, genre) == 0) {
            BoardGame* g = &store->games[i];
            printf("\nID: %d | %s | %d-%d игроков | %.2f руб. | %d шт.\n",
                   g->id, g->name, g->min_players, g->max_players, g->price, g->in_stock);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Игр жанра '%s' не найдено.\n", genre);
    }
}

void delete_game(GameStore* store) {
    int id;
    printf("Введите ID игры для удаления: ");
    scanf("%d", &id);
    
    int found_index = -1;
  
    for (int i = 0; i < store->count; i++) {
        if (store->games[i].id == id) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("Игра с ID %d не найдена.\n", id);
        return;
    }
  
    for (int i = found_index; i < store->count - 1; i++) {
        store->games[i] = store->games[i + 1];
    }
    
    store->count--;
    printf("Игра с ID %d удалена. Осталось игр: %d\n", id, store->count);
}

void edit_game(GameStore* store) {
    int id;
    printf("Введите ID игры для редактирования: ");
    scanf("%d", &id);
    
    int found_index = -1;
    
    for (int i = 0; i < store->count; i++) {
        if (store->games[i].id == id) {
            found_index = i;
            break;
        }
    }
    
    if (found_index == -1) {
        printf("Игра с ID %d не найдена.\n", id);
        return;
    }
    
    BoardGame* g = &store->games[found_index];
    printf("\nРедактирование игры: %s (ID: %d)\n", g->name, g->id);
    
    printf("Новое название (текущее: %s): ", g->name);
    scanf("%s", g->name);
    
    printf("Новый жанр (текущий: %s): ", g->genre);
    scanf("%s", g->genre);
    
    printf("Новое мин. кол-во игроков (текущее: %d): ", g->min_players);
    scanf("%d", &g->min_players);
    
    printf("Новое макс. кол-во игроков (текущее: %d): ", g->max_players);
    scanf("%d", &g->max_players);
    
    printf("Новая цена (текущая: %.2f): ", g->price);
    scanf("%f", &g->price);
    
    printf("Новое количество на складе (текущее: %d): ", g->in_stock);
    scanf("%d", &g->in_stock);
    
    printf("Игра отредактирована!\n");
}

void save_to_file(GameStore* store, char* filename) {
    FILE* file = fopen(filename, "wb");
    
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        return;
    }
    
    fwrite(&store->count, sizeof(int), 1, file);
   
    fwrite(store->games, sizeof(BoardGame), store->count, file);
    
    fclose(file);
    printf("Данные сохранены в файл '%s' (%d игр)\n", filename, store->count);
}

void load_from_file(GameStore* store, char* filename) {
    FILE* file = fopen(filename, "rb"); 
    
    if (file == NULL) {
        printf("Файл '%s' не найден. Будет создана новая база.\n", filename);
        return;
    }
    
    int count;
    fread(&count, sizeof(int), 1, file);
    
    while (store->capacity < count) {
        resize_store(store);
    }
 
    fread(store->games, sizeof(BoardGame), count, file);
    
    store->count = count;
    fclose(file);
    printf("Загружено %d игр из файла '%s'\n", count, filename);
}
