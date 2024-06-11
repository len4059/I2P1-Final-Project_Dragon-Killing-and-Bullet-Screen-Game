#ifndef bullet1_H_INCLUDED
#define bullet1_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [bullet1 object]
*/
typedef struct _bullet1
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int dir;           // 1 to the left, and -1 to the right
    double scale_factor;
    int damage;
    int changedwidth;
    int changedheight;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} bullet1;

Elements *New_bullet1(int label);
void bullet1_update(Elements *self);
void bullet1_interact(Elements *self, Elements *tar);
void bullet1_draw(Elements *self);
void bullet1_destroy(Elements *self);
void _bullet1_update_position(Elements *const ele, int dx, int dy);
void bullet1_set(Elements *const ele,int x,int y);
#endif
