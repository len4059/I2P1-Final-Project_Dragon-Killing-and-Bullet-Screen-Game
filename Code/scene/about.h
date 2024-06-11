#ifndef ABOUT_H_INCLUDED
#define ABOUT_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
    about objection
*/

typedef struct _about
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;

    int direction_x, direction_y;
    int back_x, back_y;

    bool on_back;

} about;

Scene *New_about(int label);
void about_update(Scene *self);
void about_draw(Scene *self);
void about_destroy(Scene *self);

#endif