#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "entity.h"
#include "monster.h"
#include "skills.h"
#include "item.h"

#define MAX_MESSAGES 5
char message_log[MAX_MESSAGES][80];

void add_message(const char *msg) {
    for (int i = MAX_MESSAGES - 1; i > 0; i--) {
        strcpy(message_log[i], message_log[i - 1]);
    }
    strncpy(message_log[0], msg, 79);
}

void init_game() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Player
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Monsters
    init_pair(4, COLOR_CYAN, COLOR_BLACK);   // Items
}

void cleanup_game() {
    endwin();
}

void show_help() {
    clear();
    mvprintw(1, 2, "--- HOW TO PLAY ---");
    
    attron(A_BOLD);
    mvprintw(3, 2, "Combat:");
    attroff(A_BOLD);
    mvprintw(4, 4, "Move into a monster to attack them.");
    mvprintw(5, 4, "Monsters will attack you if you are adjacent after you move.");
    
    attron(A_BOLD);
    mvprintw(7, 2, "Classes:");
    attroff(A_BOLD);
    mvprintw(8, 4, "Warrior : High HP, strong melee attack.");
    mvprintw(9, 4, "Mage    : High Mana, weaker melee but potentially strong skills.");
    mvprintw(10, 4, "Rogue   : Balanced stats, fast progression.");

    attron(A_BOLD);
    mvprintw(12, 2, "Controls:");
    attroff(A_BOLD);
    mvprintw(13, 4, "Arrows / WASD : Move and Attack");
    mvprintw(14, 4, "f             : Use Special Skill (Mage: Fireball)");
    mvprintw(15, 4, "q             : Quit Game");
    mvprintw(16, 4, "h / ?         : Show this help screen");
    
    attron(A_BOLD);
    mvprintw(18, 2, "Symbols:");
    attroff(A_BOLD);
    mvprintw(18, 4, "@ (Yellow)    : You (The Player)");
    mvprintw(19, 4, "g / o (Red)   : Monsters (Goblins / Orcs)");
    mvprintw(20, 4, "! (Cyan)      : Items (e.g., Health Potion)");
    
    mvprintw(22, 2, "Press any key to return to the game...");
    refresh();
    getch();
}

ClassType select_class() {
    int choice = 0;
    int ch;
    while (1) {
        clear();
        mvprintw(5, 10, "--- SELECT YOUR CLASS ---");
        mvprintw(7, 12, "%s Warrior", choice == 0 ? "->" : "  ");
        mvprintw(8, 12, "%s Mage", choice == 1 ? "->" : "  ");
        mvprintw(9, 12, "%s Rogue", choice == 2 ? "->" : "  ");
        
        mvprintw(11, 10, "Use Arrows/WS to select, Enter to confirm.");
        
        ch = getch();
        switch (ch) {
            case KEY_UP:
            case 'w':
                choice = (choice + 2) % 3;
                break;
            case KEY_DOWN:
            case 's':
                choice = (choice + 1) % 3;
                break;
            case '\n':
            case KEY_ENTER:
                return (ClassType)choice;
        }
    }
}

typedef struct {
    char name[32];
    char symbol;
    int color;
    int base_hp;
    int base_attack;
    int base_xp;
    int min_level;
} MonsterTemplate;

MonsterTemplate monster_templates[] = {
    {"Giant Rat", 'r', 1, 5, 2, 20, 1},
    {"Goblin", 'g', 3, 10, 4, 40, 1},
    {"Orc Warrior", 'o', 3, 20, 6, 80, 2},
    {"Skeleton", 's', 1, 15, 5, 60, 2},
    {"Dark Elf", 'e', 4, 25, 8, 120, 3},
    {"Troll", 'T', 3, 50, 12, 250, 4},
    {"Dragon Hatchling", 'd', 3, 80, 15, 500, 5}
};

#define NUM_TEMPLATES (sizeof(monster_templates) / sizeof(MonsterTemplate))

void spawn_monsters(MonsterList *monsters, Map *map, int player_level) {
    int spawned = 0;
    int target = 30; // Requested 30 monsters
    
    while (spawned < target && spawned < MAX_MONSTERS) {
        int x = rand() % MAP_WIDTH;
        int y = rand() % MAP_HEIGHT;
        
        if (map->tiles[y][x].type == TILE_FLOOR) {
            // Pick a template suitable for player level
            int template_idx = rand() % NUM_TEMPLATES;
            while (monster_templates[template_idx].min_level > player_level + 1) {
                template_idx = rand() % NUM_TEMPLATES;
            }
            
            MonsterTemplate *t = &monster_templates[template_idx];
            
            // Scale stats based on level
            float scale = 1.0 + (player_level - 1) * 0.2;
            int hp = t->base_hp * scale;
            int attack = t->base_attack * scale;
            int xp = t->base_xp * scale;
            
            monster_spawn(monsters, x, y, t->name, t->symbol, t->color, hp, attack, xp, AI_CHASE);
            spawned++;
        }
    }
}

int main() {
    init_game();

    for (int i = 0; i < MAX_MESSAGES; i++) strcpy(message_log[i], "");

    ClassType selected_class = select_class();

    Map map;
    map_init(&map);

    int start_x, start_y;
    map_generate_dungeon(&map, &start_x, &start_y);

    Entity player = {"Player", start_x, start_y, '@', 2, 20, 20, 10, 10, 5, 0, 1, 0, selected_class, AI_NONE, true};
    
    // Adjust stats based on class
    switch (selected_class) {
        case CLASS_WARRIOR:
            player.hp = player.max_hp = 30;
            player.attack = 7;
            player.mana = player.max_mana = 5;
            break;
        case CLASS_MAGE:
            player.hp = player.max_hp = 15;
            player.attack = 3;
            player.mana = player.max_mana = 20;
            break;
        case CLASS_ROGUE:
            player.hp = player.max_hp = 20;
            player.attack = 5;
            player.mana = player.max_mana = 10;
            break;
    }

    MonsterList monsters;
    monster_init_list(&monsters);
    spawn_monsters(&monsters, &map, player.level);

    ItemList items;
    item_init_list(&items);
    item_spawn(&items, start_x + 1, start_y + 1, ITEM_HEALTH_POTION);

    Skill melee = {"Melee", 0, 1, 5, SKILL_MELEE};
    Skill fireball = {"Fireball", 10, 5, 12, SKILL_FIREBALL};

    int ch;
    bool quit = false;

    while (!quit) {
        clear();
        map_compute_fov(&map, player.x, player.y, 8);
        map_render(&map);

        // Render items
        for (int i = 0; i < items.count; i++) {
            Item *it = &items.items[i];
            if (it->alive && map.tiles[it->y][it->x].visible) {
                attron(COLOR_PAIR(4));
                mvaddch(it->y, it->x, it->symbol);
                attroff(COLOR_PAIR(4));
            }
        }

        // Render monsters
        for (int i = 0; i < monsters.count; i++) {
            Entity *m = &monsters.monsters[i];
            if (m->alive && map.tiles[m->y][m->x].visible) {
                attron(COLOR_PAIR(m->color));
                mvaddch(m->y, m->x, m->symbol);
                attroff(COLOR_PAIR(m->color));
            }
        }

        // Render player
        attron(COLOR_PAIR(player.color));
        mvaddch(player.y, player.x, player.symbol);
        attroff(COLOR_PAIR(player.color));

        // Render stats
        mvprintw(MAP_HEIGHT, 0, "Lvl: %d | XP: %d/100 | HP: %d/%d | Mana: %d/%d | 'h' for help, 'q' to quit", 
                 player.level, player.xp, player.hp, player.max_hp, player.mana, player.max_mana);

        // Render messages
        for (int i = 0; i < MAX_MESSAGES; i++) {
            mvprintw(MAP_HEIGHT + 1 + i, 0, "%s", message_log[i]);
        }

        refresh();

        ch = getch();
        int new_x = player.x;
        int new_y = player.y;
        bool acted = false;

        switch (ch) {
            case 'q':
            case 'Q':
                quit = true;
                break;
            case 'h':
            case 'H':
            case '?':
                show_help();
                break;
            case 'f':
            case 'F':
                if (player.class == CLASS_MAGE) {
                    if (player.mana >= fireball.mana_cost) {
                        add_message("You cast Fireball!");
                        
                        // Copy current monster HP to see who was hit
                        int old_hps[MAX_MONSTERS];
                        bool was_alive[MAX_MONSTERS];
                        for (int i = 0; i < monsters.count; i++) {
                            old_hps[i] = monsters.monsters[i].hp;
                            was_alive[i] = monsters.monsters[i].alive;
                        }

                        skill_use(fireball, &player, &map, &monsters, &player);
                        
                        for (int i = 0; i < monsters.count; i++) {
                            Entity *m = &monsters.monsters[i];
                            if (was_alive[i]) {
                                int damage = old_hps[i] - m->hp;
                                if (damage > 0) {
                                    char msg[80];
                                    snprintf(msg, 80, "The %s is engulfed in flames for %d!", m->name, damage);
                                    add_message(msg);
                                    if (!m->alive) {
                                        snprintf(msg, 80, "The %s is incinerated! +%d XP.", m->name, m->xp_reward);
                                        add_message(msg);
                                    }
                                }
                            }
                        }
                        acted = true;
                    } else {
                        add_message("Not enough mana!");
                    }
                } else {
                    add_message("Your class has no active skill.");
                }
                break;
            case KEY_UP:
            case 'w':
                new_y--;
                break;
            case KEY_DOWN:
            case 's':
                new_y++;
                break;
            case KEY_LEFT:
            case 'a':
                new_x--;
                break;
            case KEY_RIGHT:
            case 'd':
                new_x++;
                break;
        }

        if (new_x != player.x || new_y != player.y) {
            if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT) {
                // Check for monster collision (attack)
                bool monster_hit = false;
                for (int i = 0; i < monsters.count; i++) {
                    Entity *m = &monsters.monsters[i];
                    if (m->alive && m->x == new_x && m->y == new_y) {
                        int prev_hp = m->hp;
                        skill_use(melee, &player, &map, &monsters, &player);
                        int damage = prev_hp - m->hp;
                        if (damage > 0) {
                            char msg[80];
                            snprintf(msg, 80, "You hit the %s for %d damage!", m->name, damage);
                            add_message(msg);
                            if (!m->alive) {
                                snprintf(msg, 80, "The %s dies! You gain %d XP.", m->name, m->xp_reward);
                                add_message(msg);
                            }
                        }
                        
                        monster_hit = true;
                        acted = true;
                        break;
                    }
                }

                if (!monster_hit && map.tiles[new_y][new_x].type != TILE_WALL) {
                    player.x = new_x;
                    player.y = new_y;
                    acted = true;

                    // Check for item pickup
                    for (int i = 0; i < items.count; i++) {
                        Item *it = &items.items[i];
                        if (it->alive && it->x == player.x && it->y == player.y) {
                            if (it->type == ITEM_HEALTH_POTION) {
                                player.hp += 10;
                                if (player.hp > player.max_hp) player.hp = player.max_hp;
                                it->alive = false;
                                add_message("You picked up a Health Potion!");
                            }
                        }
                    }
                }
            }
        }

        if (acted) {
            // Level up check
            if (player.xp >= 100) {
                player.level++;
                player.xp -= 100;
                player.max_hp += 10;
                player.hp = player.max_hp;
                player.max_mana += 5;
                player.mana = player.max_mana;
                player.attack += 2;
                char msg[80];
                snprintf(msg, 80, "LEVEL UP! You are now level %d!", player.level);
                add_message(msg);
            }

            monster_update_all(&monsters, &map, &player);
            // Basic monster attack player
            for (int i = 0; i < monsters.count; i++) {
                Entity *m = &monsters.monsters[i];
                if (m->alive && abs(m->x - player.x) <= 1 && abs(m->y - player.y) <= 1) {
                    player.hp -= m->attack;
                    char msg[80];
                    snprintf(msg, 80, "The %s hits you for %d damage!", m->name, m->attack);
                    add_message(msg);
                    if (player.hp <= 0) {
                        player.alive = false;
                        add_message("YOU DIED! Game Over.");
                        clear();
                        map_render(&map);
                        mvprintw(MAP_HEIGHT, 0, "Lvl: %d | XP: %d/100 | HP: %d/%d | Mana: %d/%d", 
                                 player.level, player.xp, player.hp, player.max_hp, player.mana, player.max_mana);
                        for (int j = 0; j < MAX_MESSAGES; j++) mvprintw(MAP_HEIGHT + 1 + j, 0, "%s", message_log[j]);
                        refresh();
                        getch();
                        quit = true;
                    }
                }
            }
        }
    }

    cleanup_game();
    return 0;
}
