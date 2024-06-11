#ifndef HELLFLOOR_H_INCLUDED
#define HELLFLOOR_H_INCLUDED
#include "element.h"
#include "character.h"
#include "../scene/gamescene2.h" // for element label
/*
   [floor object]
*/
typedef struct _HellFloor
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *floor_block;
    ALLEGRO_BITMAP *platform_block;
    int map_data[10][15];
} HellFloor;

Elements *New_HellFloor(int label);
void _HellFloor_load_map(HellFloor *const floor);
void HellFloor_update(Elements *const ele);
void HellFloor_interact(Elements *const, Elements *const);
void HellFloor_draw(Elements *const ele);
void HellFloor_destroy(Elements *const ele);

#endif
