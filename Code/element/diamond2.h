#ifndef diamond2_H_INCLUDED
#define diamond2_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [diamond2t object]
*/
typedef struct _diamond2
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP* img;
    Shape *hitbox; // the hitbox of object
} diamond2;

Elements *New_diamond2(int label);
void diamond2_update(Elements *self);
void diamond2_interact(Elements *self, Elements *tar);
void diamond2_draw(Elements *self);
void diamond2_destroy(Elements *self);

#endif