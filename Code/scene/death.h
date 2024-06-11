#ifndef DEATH_H_INCLUDED
#define DEATH_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
    death objection
*/

typedef struct _death
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;

    int restart_x, restart_y;
    int menu_x, menu_y;

    bool on_restart;
    bool on_menu;

} death;

Scene *New_death(int label);
void death_update(Scene *self);
void death_draw(Scene *self);
void death_destroy(Scene *self);

#endif
