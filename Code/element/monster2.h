#ifndef monster2_H_INCLUDED
#define monster2_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/gamescene2.h"
#include "../shapes/Shape.h"
/*
   [monster2 object]
*/
typedef struct _monster2
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
} monster2;

Elements *New_monster2(int label);
void monster2_update(Elements *self);
void monster2_interact(Elements *self, Elements *tar);
void monster2_draw(Elements *self);
void monster2_destory(Elements *self);

#endif
