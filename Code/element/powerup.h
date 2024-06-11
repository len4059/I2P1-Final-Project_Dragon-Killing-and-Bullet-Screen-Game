#ifndef powerup_H_INCLUDED
#define powerup_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [powerupt object]
*/
typedef struct _powerupt
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP* img;
    Shape *hitbox; // the hitbox of object
} powerup;

Elements *New_powerup(int label);
void powerup_update(Elements *self);
void powerup_interact(Elements *self, Elements *tar);
void powerup_draw(Elements *self);
void powerup_destroy(Elements *self);

#endif