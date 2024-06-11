#ifndef monster1_H_INCLUDED
#define monster1_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/gamescene2.h"
#include "../shapes/Shape.h"
/*
   [monster1 object]
*/
typedef struct _monster1
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
} monster1;

Elements *New_monster1(int label);
void monster1_update(Elements *self);
void monster1_interact(Elements *self, Elements *tar);
void monster1_draw(Elements *self);
void monster1_destory(Elements *self);

#endif
