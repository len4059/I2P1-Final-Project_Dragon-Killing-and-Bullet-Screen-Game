#ifndef FLOOR_H_INCLUDED
#define FLOOR_H_INCLUDED
#include "element.h"
#include "character.h"
#include "../scene/gamescene.h" // for element label
/*
   [floor object]
*/
typedef struct _Floor
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *floor_block;
    ALLEGRO_BITMAP *platform_block;
    int map_data[10][15];
} Floor;

Elements *New_Floor(int label);
void _Floor_load_map(Floor *const floor);
void Floor_update(Elements *const ele);
void Floor_interact(Elements *const, Elements *const);
void Floor_draw(Elements *const ele);
void Floor_destroy(Elements *const ele);

#endif
