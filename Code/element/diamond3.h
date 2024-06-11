#ifndef diamond3_H_INCLUDED
#define diamond3_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [diamond3t object]
*/
typedef struct _diamond3
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP* img;
    Shape *hitbox; // the hitbox of object
} diamond3;

Elements *New_diamond3(int label);
void diamond3_update(Elements *self);
void diamond3_interact(Elements *self, Elements *tar);
void diamond3_draw(Elements *self);
void diamond3_destroy(Elements *self);

#endif