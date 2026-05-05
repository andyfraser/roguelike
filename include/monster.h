#ifndef MONSTER_H
#define MONSTER_H

#include "entity.h"
#include "map.h"

#define MAX_MONSTERS 40

typedef struct {
    Entity monsters[MAX_MONSTERS];
    int count;
} MonsterList;

void monster_init_list(MonsterList *list);
void monster_spawn(MonsterList *list, int x, int y, const char *name, char symbol, int color, int hp, int attack, int xp_reward, AIType ai);
void monster_update_all(MonsterList *list, Map *map, Entity *player);

#endif
