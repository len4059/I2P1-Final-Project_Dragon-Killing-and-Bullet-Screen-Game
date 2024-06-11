#ifndef dust_H_INCLUDED
#define dust_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/gamescene2.h"
#include "../shapes/Shape.h"

/*
   [dustt object]
*/
typedef struct _dustt
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP* img;
    Shape *hitbox; // the hitbox of object
} dust;

Elements *New_dust(int label);
void dust_update(Elements *self);
void dust_interact(Elements *self, Elements *tar);
void dust_draw(Elements *self);
void dust_destroy(Elements *self);

#endif