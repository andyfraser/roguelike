#include "monster.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

void monster_init_list(MonsterList *list) {
    list->count = 0;
    for (int i = 0; i < MAX_MONSTERS; i++) {
        list->monsters[i].alive = false;
    }
}

void monster_spawn(MonsterList *list, int x, int y, const char *name, char symbol, int color, int hp, int attack, int xp_reward, AIType ai) {
    if (list->count < MAX_MONSTERS) {
        Entity *m = &list->monsters[list->count++];
        strncpy(m->name, name, 31);
        m->name[31] = '\0';
        m->x = x;
        m->y = y;
        m->symbol = symbol;
        m->color = color;
        m->hp = hp;
        m->max_hp = hp;
        m->attack = attack;
        m->xp_reward = xp_reward;
        m->ai = ai;
        m->alive = true;
    }
}

static void move_towards(Entity *m, int target_x, int target_y, Map *map, MonsterList *list, Entity *player) {
    int dx = target_x - m->x;
    int dy = target_y - m->y;
    float dist = sqrt(dx*dx + dy*dy);
    
    if (dist < 1.5) {
        // Attack player if adjacent (to be implemented)
        return;
    }

    int next_x = m->x + (dx > 0 ? 1 : (dx < 0 ? -1 : 0));
    int next_y = m->y + (dy > 0 ? 1 : (dy < 0 ? -1 : 0));

    if (map->tiles[next_y][next_x].type != TILE_WALL) {
        // Check collision with other monsters (simple)
        bool occupied = false;
        if (next_x == player->x && next_y == player->y) occupied = true;
        for (int i = 0; i < list->count; i++) {
            if (list->monsters[i].alive && &list->monsters[i] != m) {
                if (list->monsters[i].x == next_x && list->monsters[i].y == next_y) {
                    occupied = true;
                    break;
                }
            }
        }
        if (!occupied) {
            m->x = next_x;
            m->y = next_y;
        }
    }
}

void monster_update_all(MonsterList *list, Map *map, Entity *player) {
    for (int i = 0; i < list->count; i++) {
        Entity *m = &list->monsters[i];
        if (!m->alive) continue;

        if (m->ai == AI_CHASE) {
            move_towards(m, player->x, player->y, map, list, player);
        }
    }
}
