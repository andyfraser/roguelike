#ifndef MONSTER_DATA_H
#define MONSTER_DATA_H

#include "monster.h"

typedef struct {
    char name[32];
    char symbol;
    int color;
    int base_hp;
    int base_attack;
    int base_xp;
    int min_level;
} MonsterTemplate;

extern MonsterTemplate monster_templates[];
extern const int num_monster_templates;

#endif
