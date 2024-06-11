#ifndef ENDING_H_INCLUDED
#define ENDING_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
    ending objection
*/

typedef struct _ending
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *knight_background;
    ALLEGRO_BITMAP *supercat_background;
    ALLEGRO_BITMAP *scrolling;
    ALLEGRO_BITMAP *scrolling2;
    ALLEGRO_BITMAP *scrolling3;
    ALLEGRO_BITMAP *scrolling4;

    int restart_x, restart_y;
    int menu_x, menu_y;
    double rolling_pic_y;
    double rolling_pic_y2;
    double rolling_pic_y3;
    double rolling_pic_y4;

    bool on_restart;
    bool on_menu;

} ending;

Scene *New_ending(int label);
void ending_update(Scene *self);
void ending_draw(Scene *self);
void ending_destroy(Scene *self);

#endif
