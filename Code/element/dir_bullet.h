#ifndef dir_bullet_H_INCLUDED
#define dir_bullet_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"

/*
   [dir_bullet object]
*/
typedef struct _dir_bullet
{
    int x, y;          // the position of image
    int dx,dy;
    int width, height; // the width and height of image
    int dir;           // 1 to the left, and -1 to the right
    double scale_factor;
    int damage;
    int changedwidth;
    int changedheight;
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} dir_bullet;

Elements *New_dir_bullet(int label);
void dir_bullet_update(Elements *self);
void dir_bullet_interact(Elements *self, Elements *tar);
void dir_bullet_draw(Elements *self);
void dir_bullet_destroy(Elements *self);
void _dir_bullet_update_position(Elements *const ele, int dx, int dy);
void dir_bullet_set(Elements *const ele,int x,int y);
#endif
