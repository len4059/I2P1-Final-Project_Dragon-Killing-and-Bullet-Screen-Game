#ifndef dust2_H_INCLUDED
#define dust2_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/gamescene2.h"
#include "../shapes/Shape.h"

/*
   [dust2t object]
*/
typedef struct _dust2t
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP* img;
    Shape *hitbox; // the hitbox of object
} dust2;

Elements *New_dust2(int label);
void dust2_update(Elements *self);
void dust2_interact(Elements *self, Elements *tar);
void dust2_draw(Elements *self);
void dust2_destroy(Elements *self);

#endif