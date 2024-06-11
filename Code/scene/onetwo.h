#ifndef ONETWO_H_INCLUDED
#define ONETWO_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
    onetwo objection
*/

typedef struct _onetwo
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;

    double timer;

} onetwo;

Scene *New_onetwo(int label);
void onetwo_update(Scene *self);
void onetwo_draw(Scene *self);
void onetwo_destroy(Scene *self);

#endif
