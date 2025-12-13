#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boardgame.h"

int main() {
    baza a;
    a.games = NULL;
    a.count = 0;
    a.capacity = 0;

    char filename[100];
    printf("Введите имя файла для загрузки: ");
    scanf("%99s", filename); 
    
    load(filename, &a);
    
    int option;
    char title[100];
    char genre[50];
    
    do {
        printf("\n=== МАГАЗИН НАСТОЛЬНЫХ ИГР ===\n");
        printf("1. Вывести все игры\n");
        printf("2. Добавить игру\n");
        printf("3. Удалить игру\n");
        printf("4. Найти игру\n");
        printf("5. Изменить информацию об игре\n");
        printf("6. Завершить работу\n");
        printf("Введите выбранное число: ");
        scanf("%d", &option);
        
        switch(option) {
            case 1:
                all_vivod(&a);
                break;
            case 2:
                add(&a, 1);
                save("boardgames.txt", &a);
                all_vivod(&a);
                break;
            case 3:
                printf("Название игры для удаления: ");
                scanf("%s", title);
                delite(&a, title);
                save("boardgames.txt", &a);
                all_vivod(&a);
                break;
            case 4:
                printf("Название игры для поиска: ");
                scanf("%s", title);
                printf("Жанр игры: ");
                scanf("%s", genre);
                search(&a, title, genre);
                break;
            case 5:
                printf("Название игры для редактирования: ");
                scanf("%s", title);
                redact(&a, title);
                save("boardgames.txt", &a);
                all_vivod(&a);
                break;
            case 6:
                printf("Завершение работы...\n");
                break;
            default:
                printf("Некорректный выбор, попробуйте еще раз\n");
                break;
        }
    } while (option != 6);
    
    save(filename, &a);
    free_baza(&a);
    
    return 0;
}
