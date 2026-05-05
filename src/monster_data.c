#include "monster_data.h"

MonsterTemplate monster_templates[] = {
    // Level 1: Weak pests and basic threats
    {"Giant Rat", 'r', 1, 5, 2, 20, 1},
    {"Cave Bat", 'b', 1, 4, 1, 15, 1},
    {"Green Slime", 's', 5, 8, 3, 30, 1},
    {"Goblin Scout", 'g', 3, 10, 4, 40, 1},
    {"Giant Spider", 'S', 3, 12, 5, 50, 1},
    {"Viper", '~', 5, 6, 4, 25, 1},
    {"Kobold", 'k', 3, 9, 3, 35, 1},
    {"Fire Beetle", 'B', 2, 7, 4, 30, 1},
    {"Cave Crab", 'c', 4, 11, 2, 35, 1},
    {"Sewer Newt", 'n', 5, 5, 2, 20, 1},

    // Level 2: Undead and stronger humanoids
    {"Zombie", 'z', 5, 15, 3, 45, 2},
    {"Skeleton", 'k', 1, 18, 5, 60, 2},
    {"Orc Grunt", 'o', 3, 25, 7, 85, 2},
    {"Gnoll Hunter", 'G', 4, 22, 6, 75, 2},
    {"Restless Ghost", 'h', 1, 10, 8, 100, 2},
    {"Acid Jelly", 'j', 7, 30, 4, 90, 2},
    {"Hobgoblin Warrior", 'H', 3, 20, 8, 80, 2},
    {"Gray Wolf", 'w', 1, 16, 6, 70, 2},
    {"Giant Toad", 'T', 5, 28, 5, 95, 2},
    {"Shadow Spirit", 'f', 6, 12, 10, 110, 2},

    // Level 3: Magical beings and skilled fighters
    {"Dark Elf Archer", 'e', 6, 28, 9, 130, 3},
    {"Stone Gargoyle", 'H', 1, 40, 6, 150, 3},
    {"Treasure Mimic", 'M', 4, 35, 10, 180, 3},
    {"Harpy", 'P', 7, 32, 8, 140, 3},
    {"Centaur Scout", 'C', 4, 45, 11, 200, 3},
    {"Rust Monster", 'R', 2, 30, 7, 160, 3},
    {"Gelatinous Cube", 'J', 4, 55, 5, 220, 3},
    {"Minor Imp", 'i', 3, 22, 12, 170, 3},
    {"Carrion Crawler", 'E', 5, 38, 9, 190, 3},
    {"Owlbear", 'Y', 1, 50, 13, 250, 3},

    // Level 4: Heavy hitters and dangerous beasts
    {"Minotaur", 'T', 3, 60, 15, 300, 4},
    {"Ogre", 'O', 5, 70, 14, 350, 4},
    {"Wraith", 'W', 6, 40, 18, 400, 4},
    {"Banshee", 'B', 1, 35, 20, 450, 4},
    {"Clay Golem", 'X', 1, 100, 10, 500, 4},
    {"Ettin", 'N', 3, 85, 16, 420, 4},
    {"Manticore", 'm', 7, 75, 17, 480, 4},
    {"Medusa", 'U', 5, 55, 22, 550, 4},
    {"Wyvern", 'v', 5, 90, 19, 600, 4},
    {"Basilisk", 'b', 5, 65, 21, 520, 4},

    // Level 5: Elemental giants and rare spawn
    {"Dragon Hatchling", 'd', 3, 80, 15, 500, 5},
    {"Chimera", 'K', 7, 90, 18, 600, 5},
    {"Elder Lich", 'L', 6, 70, 25, 800, 5},
    {"Vampire Lord", 'V', 3, 85, 22, 750, 5},
    {"Flesh Golem", 'f', 5, 120, 15, 700, 5},
    {"Naga Myrmidon", 'N', 4, 100, 20, 850, 5},
    {"Hydra", 'Y', 5, 130, 24, 950, 5},
    {"Fire Giant", 'F', 3, 140, 26, 1100, 5},
    {"Frost Giant", 'I', 6, 145, 25, 1150, 5},
    {"Stone Giant", 'S', 1, 150, 22, 1050, 5},

    // Level 6: High-tier demons and monsters
    {"Beholder", 'E', 7, 120, 20, 1000, 6},
    {"Greater Demon", 'D', 3, 150, 25, 1500, 6},
    {"Iron Golem", 'I', 1, 200, 18, 1300, 6},
    {"Marilith", 'M', 3, 160, 30, 1800, 6},
    {"Balor", 'p', 3, 180, 35, 2200, 6},
    {"Kraken", 'K', 6, 220, 28, 2500, 6},
    {"Rakshasa", 'R', 7, 110, 32, 1700, 6},
    {"Mind Flayer", 'P', 7, 90, 40, 2000, 6},
    {"Guardian Sphinx", 'X', 2, 140, 28, 1600, 6},
    {"Phoenix", 'A', 3, 130, 34, 1900, 6},

    // Level 7: Ancient dragons and elite guardians
    {"Ancient Dragon", 'A', 3, 250, 35, 3000, 7},
    {"Storm Giant", 's', 6, 200, 38, 3500, 7},
    {"Dracolich", 'D', 6, 220, 42, 4500, 7},
    {"Death Knight", 'K', 3, 180, 45, 4000, 7},
    {"Pit Fiend", 'F', 3, 240, 48, 5500, 7},
    {"Solar Angel", 'S', 2, 210, 50, 5000, 7},
    {"Purple Worm", 'w', 7, 280, 35, 4200, 7},
    {"Remorhaz", 'Z', 6, 230, 40, 3800, 7},
    {"Efreeti Sultan", 'E', 3, 170, 44, 4300, 7},
    {"Djinni Vizier", 'J', 4, 175, 43, 4100, 7},

    // Level 8: Mythical titans and behemoths
    {"Stone Titan", 'Z', 4, 300, 40, 5000, 8},
    {"The Tarrasque", 'T', 5, 500, 50, 10000, 8},
    {"Gold Dragon", 'g', 2, 350, 55, 8000, 8},
    {"Great Wyrm", 'W', 3, 400, 60, 9500, 8},
    {"Archdemon", 'A', 3, 380, 65, 12000, 8},
    {"Archangel", 'a', 2, 360, 64, 11500, 8},
    {"Behemoth", 'B', 1, 450, 55, 9000, 8},
    {"Leviathan", 'l', 6, 480, 52, 9800, 8},
    {"Demilich", 'd', 1, 150, 80, 15000, 8},
    {"Void Stalker", 'v', 6, 250, 75, 13000, 8},

    // Level 9: Eldritch horrors and reality warpers
    {"Star Spawn", '*', 7, 600, 85, 20000, 9},
    {"Ancient Old One", '&', 6, 800, 95, 30000, 9},
    {"Cosmic Horror", '?', 7, 700, 100, 25000, 9},
    {"Reality Warper", '@', 4, 550, 110, 35000, 9},
    {"Chrono Dragon", 'C', 4, 750, 90, 28000, 9},
    {"Chaos Elemental", 'E', 7, 650, 105, 22000, 9},
    {"Void Reaver", 'V', 6, 720, 98, 24000, 9},
    {"Abyssal Lord", 'L', 3, 850, 120, 40000, 9},
    {"Celestial Warden", 'W', 2, 820, 115, 38000, 9},
    {"Nightmare King", 'N', 3, 680, 108, 27000, 9},

    // Level 10: Deities and endgame bosses
    {"God Slayer", 'X', 3, 1200, 150, 75000, 10},
    {"World Eater", 'O', 5, 1500, 140, 100000, 10},
    {"Chaos Avatar", 'C', 7, 1100, 160, 90000, 10},
    {"Seraph of Death", 'S', 1, 1000, 170, 85000, 10},
    {"Infernal Emperor", 'I', 3, 1300, 145, 95000, 10},
    {"Astral Titan", 'T', 4, 1400, 135, 80000, 10},
    {"Void Dragon", 'D', 6, 1250, 155, 110000, 10},
    {"Elder Brain", 'B', 7, 900, 180, 120000, 10},
    {"The Architect", 'A', 2, 1600, 130, 150000, 10},
    {"Omega Prime", '#', 1, 2000, 200, 250000, 10}
};

const int num_monster_templates = sizeof(monster_templates) / sizeof(MonsterTemplate);
