#ifndef SKILLS_H
#define SKILLS_H

#include "entity.h"
#include "map.h"
#include "monster.h"

typedef enum {
    SKILL_MELEE,
    SKILL_CLEAVE,
    SKILL_FIREBALL,
    SKILL_DASH
} SkillType;

typedef struct {
    char name[32];
    int mana_cost;
    int range;
    int damage;
    SkillType type;
} Skill;

void skill_use(Skill skill, Entity *user, Map *map, MonsterList *monsters, Entity *player);

#endif
