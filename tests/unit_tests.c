#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "map.h"
#include "entity.h"
#include "monster.h"
#include "skills.h"

// Helper to check if a tile is within bounds
bool is_in_bounds(int x, int y) {
    return x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT;
}

void test_map_init() {
    printf("Testing map_init...\n");
    Map map;
    map_init(&map);
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            assert(map.tiles[y][x].type == TILE_WALL);
            assert(map.tiles[y][x].visible == false);
            assert(map.tiles[y][x].explored == false);
        }
    }
    printf("map_init passed!\n");
}

void test_fov() {
    printf("Testing map_compute_fov...\n");
    Map map;
    map_init(&map);
    
    // Create a small 5x5 room of floors
    for (int y = 10; y < 15; y++) {
        for (int x = 10; x < 15; x++) {
            map.tiles[y][x].type = TILE_FLOOR;
        }
    }
    
    map_compute_fov(&map, 12, 12, 5);
    
    assert(map.tiles[12][12].visible == true);
    assert(map.tiles[12][12].explored == true);
    // Floor tiles around should be visible
    assert(map.tiles[11][11].visible == true);
    assert(map.tiles[13][13].visible == true);
    
    // Far away tiles should not be visible
    assert(map.tiles[0][0].visible == false);
    printf("map_compute_fov passed!\n");
}

void test_monster_spawn() {
    printf("Testing monster_spawn...\n");
    MonsterList monsters;
    monster_init_list(&monsters);
    assert(monsters.count == 0);
    
    monster_spawn(&monsters, 10, 10, "Test Monster", 'T', 1, 20, 5, 50, AI_CHASE);
    assert(monsters.count == 1);
    assert(monsters.monsters[0].alive == true);
    assert(monsters.monsters[0].x == 10);
    assert(monsters.monsters[0].y == 10);
    assert(strcmp(monsters.monsters[0].name, "Test Monster") == 0);
    assert(monsters.monsters[0].hp == 20);
    printf("monster_spawn passed!\n");
}

void test_skills_melee() {
    printf("Testing skill_use (Melee)...\n");
    Map map;
    map_init(&map);
    
    MonsterList monsters;
    monster_init_list(&monsters);
    monster_spawn(&monsters, 11, 11, "Dummy", 'd', 1, 10, 2, 10, AI_CHASE);
    
    Entity player = {"Player", 10, 10, '@', 2, 20, 20, 10, 10, 5, 0, 1, 0, CLASS_WARRIOR, AI_NONE, true, {"None", 0, WEAPON_NONE}};
    Skill melee = {"Melee", 0, 1, 5, SKILL_MELEE};
    
    // Player at (10,10), Monster at (11,11) -> adjacent
    skill_use(melee, &player, &map, &monsters, &player);
    
    // Monster should have taken 5 (skill) + 5 (player attack) = 10 damage
    assert(monsters.monsters[0].hp <= 0);
    assert(monsters.monsters[0].alive == false);
    assert(player.xp == 10); // Gained XP reward
    printf("skill_use (Melee) passed!\n");
}

void test_skills_fireball() {
    printf("Testing skill_use (Fireball)...\n");
    Map map;
    map_init(&map);
    
    // Make tiles visible for fireball to work
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map.tiles[y][x].visible = true;
        }
    }
    
    MonsterList monsters;
    monster_init_list(&monsters);
    monster_spawn(&monsters, 11, 11, "Monster 1", 'm', 1, 10, 2, 10, AI_CHASE);
    monster_spawn(&monsters, 12, 12, "Monster 2", 'm', 1, 10, 2, 10, AI_CHASE);
    
    Entity player = {"Player", 10, 10, '@', 2, 20, 20, 20, 20, 5, 0, 1, 0, CLASS_MAGE, AI_NONE, true, {"None", 0, WEAPON_NONE}};
    Skill fireball = {"Fireball", 10, 5, 12, SKILL_FIREBALL};
    
    skill_use(fireball, &player, &map, &monsters, &player);
    
    // Both monsters should be dead (damage 12 > HP 10)
    assert(monsters.monsters[0].alive == false);
    assert(monsters.monsters[1].alive == false);
    assert(player.mana == 10); // 20 - 10 cost
    assert(player.xp == 20); // 10 + 10 XP
    printf("skill_use (Fireball) passed!\n");
}

void test_monster_movement_bounds() {
    printf("Testing monster movement bounds...\n");
    Map map;
    map_init(&map);
    MonsterList list;
    monster_init_list(&list);
    Entity player = {"Player", 50, 20, '@', 2, 20, 20, 10, 10, 5, 0, 1, 0, CLASS_WARRIOR, AI_NONE, true, {"None", 0, WEAPON_NONE}};
    
    // Spawn monster at the edge
    monster_spawn(&list, 0, 0, "Test Monster", 'M', 3, 10, 2, 10, AI_CHASE);
    
    // Monster should stay in bounds even if trying to move out (towards player is in bounds here, but let's test -1)
    list.monsters[0].x = 0;
    list.monsters[0].y = 0;
    player.x = -10; // Player way off to the left
    player.y = -10; // Player way off to the top
    
    monster_update_all(&list, &map, &player);
    
    // Should stay at (0,0) or at least not go negative
    assert(list.monsters[0].x >= 0);
    assert(list.monsters[0].y >= 0);
    
    printf("monster movement bounds passed!\n");
}

int main() {
    test_map_init();
    test_fov();
    test_monster_spawn();
    test_skills_melee();
    test_skills_fireball();
    test_monster_movement_bounds();
    
    printf("\nALL TESTS PASSED!\n");
    return 0;
}
