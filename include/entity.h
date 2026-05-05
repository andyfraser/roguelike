#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

typedef enum {
    AI_NONE,
    AI_CHASE
} AIType;

typedef enum {
    CLASS_WARRIOR,
    CLASS_MAGE,
    CLASS_ROGUE
} ClassType;

typedef enum {
    WEAPON_NONE,
    WEAPON_SWORD,
    WEAPON_AXE,
    WEAPON_STAFF
} WeaponType;

typedef struct {
    char name[32];
    int damage_bonus;
    WeaponType type;
} Weapon;

typedef struct {
    char name[32];
    int x, y;
    char symbol;
    int color;
    int hp;
    int max_hp;
    int mana;
    int max_mana;
    int attack;
    int xp;
    int level;
    int xp_reward;
    ClassType class;
    AIType ai;
    bool alive;
    Weapon weapon;
} Entity;

#endif
