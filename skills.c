#include "skills.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>

void skill_use(Skill skill, Entity *user, Map *map, MonsterList *monsters, Entity *player) {
    (void)map;
    (void)player;
    if (user->mana < skill.mana_cost) return;
    user->mana -= skill.mana_cost;

    // Basic combat resolution
    if (skill.type == SKILL_MELEE) {
        // Find adjacent target
        for (int i = 0; i < monsters->count; i++) {
            Entity *m = &monsters->monsters[i];
            if (m->alive && abs(m->x - user->x) <= 1 && abs(m->y - user->y) <= 1) {
                int damage = user->attack + skill.damage;
                m->hp -= damage;
                
                if (m->hp <= 0) {
                    m->alive = false;
                    user->xp += m->xp_reward;
                }
                break;
            }
        }
    } else if (skill.type == SKILL_FIREBALL) {
        for (int i = 0; i < monsters->count; i++) {
            Entity *m = &monsters->monsters[i];
            float dist = sqrt(pow(m->x - user->x, 2) + pow(m->y - user->y, 2));
            if (m->alive && dist <= skill.range && map->tiles[m->y][m->x].visible) {
                int damage = skill.damage;
                m->hp -= damage;
                if (m->hp <= 0) {
                    m->alive = false;
                    user->xp += m->xp_reward;
                }
            }
        }
    }
}
