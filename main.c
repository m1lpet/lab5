#include "boardgame.h"
#include <stdio.h>

#define FILENAME "games.dat"

void print_menu() {
    printf("\n=== МАГАЗИН НАСТОЛЬНЫХ ИГР ===\n");
    printf("1. Показать все игры\n");
    printf("2. Добавить игру\n");
    printf("3. Найти по названию\n");
    printf("4. Найти по жанру\n");
    printf("5. Удалить игру\n");
    printf("6. Редактировать игру\n");
    printf("7. Сохранить в файл\n");
    printf("8. Загрузить из файла\n");
    printf("0. Выход\n");
    printf("Выберите действие: ");
}

int main() {
    GameStore store;
    int choice;
    
    init_store(&store);
    printf("Магазин настольных игр инициализирован!\n");
    printf("Текущая вместимость: %d игр\n", store.capacity);
    
    load_from_file(&store, FILENAME);
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                show_all(&store);
                break;
            case 2:
                add_game(&store);
                break;
            case 3:
                search_by_name(&store);
                break;
            case 4:
                search_by_genre(&store);
                break;
            case 5:
                delete_game(&store);
                break;
            case 6:
                edit_game(&store);
                break;
            case 7:
                save_to_file(&store, FILENAME);
                break;
            case 8:
                load_from_file(&store, FILENAME);
                break;
            case 0:
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while(choice != 0);
    
    save_to_file(&store, FILENAME);
   
    free_store(&store);
    printf("Память освобождена. До свидания!\n");
    
    return 0;
}
