#ifndef ONEONE_H_INCLUDED
#define ONEONE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
    oneone objection
*/

typedef struct _oneone
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;

    double timer;

} oneone;

Scene *New_oneone(int label);
void oneone_update(Scene *self);
void oneone_draw(Scene *self);
void oneone_destroy(Scene *self);

#endif
