#ifndef trace_bullet_H_INCLUDED
#define trace_bullet_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [trace_bullet object]
*/
typedef struct _trace_bullet
{
    int x, y;          // the position of image
    int dx,dy;
    int width, height; // the width and height of image
    int dir;           // 1 to the left, and -1 to the right
    double scale_factor;
    int damage;
    int changedwidth;
    int changedheight;
    int speed;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} trace_bullet;

Elements *New_trace_bullet(int label);
void trace_bullet_update(Elements *self);
void trace_bullet_interact(Elements *self, Elements *tar);
void trace_bullet_draw(Elements *self);
void trace_bullet_destroy(Elements *self);
void _trace_bullet_update_position(Elements *const ele, int dx, int dy);
void trace_bullet_set(Elements *const ele,int x,int y);
#endif
