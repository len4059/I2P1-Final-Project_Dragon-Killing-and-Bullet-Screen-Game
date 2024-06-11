#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"

/*
   [character object]
*/
typedef enum CharacterType
{
	STOP = 0,
	MOVE,
	ATK,
    JUMP
} CharacterType;
typedef struct _Character
{
    int score;
    int x, y;
    int dx,dy;
    bool airborne;       
    int width, height; // the width and height of image
    bool dir;          // true: face to right, false: face to left
    int state;         // the state of character
    bool death;
    int inity;
    int hp;
    int hpx;
    int hpy;
    int hpw;
    int hph;
    int iframe;
    int maxhp;
    int shootcount;
    int dashframe;
    int pushbackframe;
    bool invincible;
    ALLEGRO_BITMAP *healthbar;
    ALGIF_ANIMATION* gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;
    Shape *hitbox; // the hitbox of object
} Character;
Elements *New_Character(int label);
void Character_setinvincible(Elements *const self,bool set);
void _Character_update_position(Elements *const self, int dx, int dy);
void Character_update(Elements *const self);
void Character_interact(Elements *const self, Elements *const target);
void Character_draw(Elements *const self);
void Character_destory(Elements *const self);
void Character_death(Elements *const ele);
#endif
