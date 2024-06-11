#ifndef monster4_H_INCLUDED
#define monster4_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/gamescene2.h"
#include "../shapes/Shape.h"
/*
   [monster4 object]
*/
typedef struct _monster4
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int dir;
    int x_pos_max;
    int x_pos_min;
    int damage;
    bool death;
    double scale_factor;

    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} monster4;

Elements *New_monster4(int label);
void monster4_update(Elements *self);
void monster4_interact(Elements *self, Elements *tar);
void monster4_draw(Elements *self);
void monster4_destory(Elements *self);

#endif
