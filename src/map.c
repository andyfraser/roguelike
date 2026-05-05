#include "map.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_ROOMS 30
#define ROOM_MIN_SIZE 4
#define ROOM_MAX_SIZE 12

void create_room(Map *map, Rect room) {
    for (int y = room.y1 + 1; y < room.y2; y++) {
        for (int x = room.x1 + 1; x < room.x2; x++) {
            map->tiles[y][x].type = TILE_FLOOR;
        }
    }
}

void create_h_tunnel(Map *map, int x1, int x2, int y) {
    for (int x = (x1 < x2 ? x1 : x2); x <= (x1 > x2 ? x1 : x2); x++) {
        map->tiles[y][x].type = TILE_FLOOR;
    }
}

void create_v_tunnel(Map *map, int y1, int y2, int x) {
    for (int y = (y1 < y2 ? y1 : y2); y <= (y1 > y2 ? y1 : y2); y++) {
        map->tiles[y][x].type = TILE_FLOOR;
    }
}

bool rect_intersect(Rect r1, Rect r2) {
    return (r1.x1 <= r2.x2 && r1.x2 >= r2.x1 &&
            r1.y1 <= r2.y2 && r1.y2 >= r2.y1);
}

void map_init(Map *map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->tiles[y][x].type = TILE_WALL;
            map->tiles[y][x].visible = false;
            map->tiles[y][x].explored = false;
        }
    }
}

void map_generate_dungeon(Map *map, int *player_start_x, int *player_start_y) {
    static bool seeded = false;
    if (!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    Rect rooms[MAX_ROOMS];
    int num_rooms = 0;

    for (int r = 0; r < MAX_ROOMS; r++) {
        int w = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
        int h = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
        int x = rand() % (MAP_WIDTH - w - 1);
        int y = rand() % (MAP_HEIGHT - h - 1);

        Rect new_room = {x, y, x + w, y + h};

        bool intersect = false;
        for (int i = 0; i < num_rooms; i++) {
            if (rect_intersect(new_room, rooms[i])) {
                intersect = true;
                break;
            }
        }

        if (!intersect) {
            create_room(map, new_room);

            int curr_center_x = (new_room.x1 + new_room.x2) / 2;
            int curr_center_y = (new_room.y1 + new_room.y2) / 2;

            if (num_rooms == 0) {
                *player_start_x = curr_center_x;
                *player_start_y = curr_center_y;
            } else {
                int prev_center_x = (rooms[num_rooms - 1].x1 + rooms[num_rooms - 1].x2) / 2;
                int prev_center_y = (rooms[num_rooms - 1].y1 + rooms[num_rooms - 1].y2) / 2;

                if (rand() % 2 == 1) {
                    create_h_tunnel(map, prev_center_x, curr_center_x, prev_center_y);
                    create_v_tunnel(map, prev_center_y, curr_center_y, curr_center_x);
                } else {
                    create_v_tunnel(map, prev_center_y, curr_center_y, prev_center_x);
                    create_h_tunnel(map, prev_center_x, curr_center_x, curr_center_y);
                }
            }

            rooms[num_rooms] = new_room;
            num_rooms++;
        }
    }
}

void map_compute_fov(Map *map, int player_x, int player_y, int radius) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map->tiles[y][x].visible = false;
        }
    }

    for (int i = 0; i < 360; i++) {
        float rad = i * (M_PI / 180.0f);
        float x = (float)player_x + 0.5f;
        float y = (float)player_y + 0.5f;

        for (int r = 0; r < radius; r++) {
            int tx = (int)x;
            int ty = (int)y;

            if (tx < 0 || tx >= MAP_WIDTH || ty < 0 || ty >= MAP_HEIGHT) break;

            map->tiles[ty][tx].visible = true;
            map->tiles[ty][tx].explored = true;

            if (map->tiles[ty][tx].type == TILE_WALL) break;

            x += cosf(rad);
            y += sinf(rad);
        }
    }
}

void map_render(Map *map) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (!map->tiles[y][x].explored) {
                mvaddch(y, x, ' ');
                continue;
            }

            char symbol;
            switch (map->tiles[y][x].type) {
                case TILE_WALL:
                    symbol = '#';
                    break;
                case TILE_FLOOR:
                    symbol = '.';
                    break;
                default:
                    symbol = ' ';
                    break;
            }

            if (map->tiles[y][x].visible) {
                attron(A_BOLD);
                mvaddch(y, x, symbol);
                attroff(A_BOLD);
            } else {
                attron(A_DIM);
                mvaddch(y, x, symbol);
                attroff(A_DIM);
            }
        }
    }
}
