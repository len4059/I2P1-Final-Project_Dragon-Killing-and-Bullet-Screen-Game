#ifndef DRESS_H_INCLUDED
#define DRESS_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

typedef struct _dress
{

    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *knight;
    ALLEGRO_BITMAP *supercat;
    ALLEGRO_BITMAP *background;
    int knight_x, knight_y;
    int supercat_x, supercat_y;
    int back_x, back_y;
    int who_selected;

    bool on_back;

} dress;

Scene *New_dress(int label);
void dress_update(Scene *self);
void dress_draw(Scene *self);
void dress_destroy(Scene *self);

#endif
