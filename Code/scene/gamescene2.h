#ifndef GAMESCENE2_H_INCLUDED
#define GAMESCENE2_H_INCLUDED
#include "scene.h"
#include "allelements.h"
#include "../element/element.h"
#include "../element/character.h"
#include "../element/hellfloor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/monster1.h"
#include "../element/monster3.h"
#include "../element/monster4.h"
#include "../element/turret1.h"
#include "../element/bullet1.h"
#include "../element/dir_bullet.h"
#include "../element/trace_bullet.h"
#include "../element/diamond.h"
#include "../element/boss.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/*typedef enum EleType2
{
    HellFloor_L,
    Teleport_L,
    Tree_L,
    Character_L,
    Projectile_L,
    monster1_L,
    turret1_L,
    bullet1_L,
    dir_bullet_L,
    trace_bullet_L,
    diamond_L
} EleType2;*/

typedef struct _GameScene2
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE *meow;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_SAMPLE_INSTANCE *meow_instance;
    double shoot_time;
    bool pause; // esc in the game
    int frame;
    bool on_continue;
    bool on_menu;

} GameScene2;

Scene *New_GameScene2(int label);
void game_scene2_update(Scene *self);
void game_scene2_draw(Scene *self);
void game_scene2_destroy(Scene *self);

#endif