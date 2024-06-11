#ifndef monster3_H_INCLUDED
#define monster3_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/gamescene2.h"
#include "../shapes/Shape.h"
/*
   [monster3 object]
*/
typedef struct _monster3
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
} monster3;

Elements *New_monster3(int label);
void monster3_update(Elements *self);
void monster3_interact(Elements *self, Elements *tar);
void monster3_draw(Elements *self);
void monster3_destory(Elements *self);

#endif
