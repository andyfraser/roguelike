#include "item.h"
#include <ncurses.h>

void item_init_list(ItemList *list) {
    list->count = 0;
    for (int i = 0; i < MAX_ITEMS; i++) {
        list->items[i].alive = false;
    }
}

void item_spawn(ItemList *list, int x, int y, ItemType type) {
    if (list->count < MAX_ITEMS) {
        Item *it = &list->items[list->count++];
        it->x = x;
        it->y = y;
        it->type = type;
        it->alive = true;
        
        switch (type) {
            case ITEM_HEALTH_POTION:
                it->symbol = '!';
                it->color = 1; // White for now, maybe custom later
                break;
        }
    }
}
