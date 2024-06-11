#ifndef DIAMOND_H_INCLUDED
#define DIAMOND_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [diamondt object]
*/
typedef struct _diamondt
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP* img;
    Shape *hitbox; // the hitbox of object
} diamond;

Elements *New_diamond(int label);
void diamond_update(Elements *self);
void diamond_interact(Elements *self, Elements *tar);
void diamond_draw(Elements *self);
void diamond_destroy(Elements *self);

#endif