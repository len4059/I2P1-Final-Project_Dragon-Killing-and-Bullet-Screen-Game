#ifndef boss_H_INCLUDED
#define boss_H_INCLUDED
#include "element.h"
#include "../scene/gamescene2.h" // for element label
#include "../shapes/Shape.h"
/*
   [boss object]
*/
typedef struct _boss
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int dir;
    int x_pos_max;
    int x_pos_min;
    int damage;
    bool death;
    double scale_factor;
    int hp;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} boss;
Elements *New_boss(int label);
void boss_update(Elements *self);
void boss_interact(Elements *self, Elements *tar);
void boss_draw(Elements *self);
void boss_destory(Elements *self);
void boss_death(Elements *self);
#endif
