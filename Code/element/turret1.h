#ifndef TURRET1_H_INCLUDED
#define TURRET1_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [turret1 object]
*/
typedef struct _turret1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int dir;           // 1 to the left, and -1 to the right
    double scale_factor;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} turret1;

Elements *New_turret1(int label);
void turret1_update(Elements *self);
void turret1_interact(Elements *self, Elements *tar);
void turret1_draw(Elements *self);
void turret1_destroy(Elements *self);

#endif
