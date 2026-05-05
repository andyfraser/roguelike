#ifndef ITEM_H
#define ITEM_H

#include "stdbool.h"

typedef enum {
    ITEM_HEALTH_POTION
} ItemType;

typedef struct {
    int x, y;
    char symbol;
    int color;
    ItemType type;
    bool alive;
} Item;

#define MAX_ITEMS 10

typedef struct {
    Item items[MAX_ITEMS];
    int count;
} ItemList;

void item_init_list(ItemList *list);
void item_spawn(ItemList *list, int x, int y, ItemType type);

#endif
