#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char genre[50];
    int players;
    int age;
    float price;
    int stock;
} boardgame;

typedef struct {
    boardgame* games;   
    int count;         
    int capacity;      
} baza;

void all_vivod(baza* a);
void add(baza* a, int f);
void delite(baza* a, char* name);
void search(baza* a, char* name, char* genre);
void redact(baza* a, char* name);
void save(const char* filename, baza* a);
void load(char* filename, baza* a);
void free_baza(baza* a);

#endif
