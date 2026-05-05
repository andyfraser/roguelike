#ifndef MAP_H
#define MAP_H

#include <stdbool.h>

#define MAP_WIDTH 132
#define MAP_HEIGHT 40

typedef enum {
    TILE_WALL,
    TILE_FLOOR
} TileType;

typedef struct {
    TileType type;
    bool visible;
    bool explored;
} Tile;

typedef struct {
    Tile tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

void map_init(Map *map);
void map_generate_dungeon(Map *map, int *player_start_x, int *player_start_y);
void map_render(Map *map);
void map_compute_fov(Map *map, int player_x, int player_y, int radius);

typedef struct {
    int x1, y1, x2, y2;
} Rect;

#endif
