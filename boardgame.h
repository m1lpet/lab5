#ifndef BOARDGAME_H
#define BOARDGAME_H

#define MAX_NAME 50
#define MAX_GENRE 30

typedef struct {
    int id;
    char name[MAX_NAME];
    char genre[MAX_GENRE];
    int min_players;
    int max_players;
    float price;
    int in_stock;
} BoardGame;

typedef struct {
    BoardGame* games;  
    int count;         
    int capacity;     
} GameStore;

void init_store(GameStore* store);                  
void free_store(GameStore* store);                   
void add_game(GameStore* store);                      
void show_all(GameStore* store);                    
void search_by_name(GameStore* store);              
void search_by_genre(GameStore* store);                
void delete_game(GameStore* store);                  
void edit_game(GameStore* store);                      
void save_to_file(GameStore* store, char* filename);   
void load_from_file(GameStore* store, char* filename); 

#endif
