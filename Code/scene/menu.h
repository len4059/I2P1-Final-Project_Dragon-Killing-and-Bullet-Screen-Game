#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

/*
   [Menu object]
*/
typedef struct _Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *title;
    ALLEGRO_BITMAP *knight;
    ALLEGRO_BITMAP *supercat;
    
    int play_x, play_y;
    int about_x, about_y;
    int dress_x, dress_y;
    int exit_x, exit_y;

    bool on_play;
    bool on_about;
    bool on_dress;
    bool on_exit;

} Menu;
Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

#endif
