#include "gamescene.h"
#include "../element/bullet1.h"
#include "../element/dir_bullet.h"
#include "../element/trace_bullet.h"
#include "../element/diamond.h"
#include "../element/diamond2.h"
#include "../element/diamond3.h"
#include "../element/monster1.h"
#include "../element/monster2.h"
#include "../element/powerup.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

/*
   [GameScene function]
*/

int log_score = 0;
double level_one_log_time = 0.0;
double start_time;

Scene *New_GameScene(int label)
{
    int level_one_finish = 0;
    log_score = 0;
    level_one_log_time = 0.0;
    start_time = al_get_time();

    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.png");
    pDerivedObj->shoot_time = 0; // Initialize the timer
    pDerivedObj->pause = false;  // Initialize pause status
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0); 

    pDerivedObj->song = al_load_sample("assets/sound/gamescene.mp3");
    pDerivedObj->meow = al_load_sample("assets/sound/meow.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->meow_instance = al_create_sample_instance(pDerivedObj->meow);
    if(pDerivedObj->song) printf("123");

    pDerivedObj->on_continue = false;
    pDerivedObj->on_menu = false;

    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    //al_set_sample_instance_playmode(pDerivedObj->meow_instance, ALLEGRO_PLAYMODE_LOOP);
    if(pDerivedObj->sample_instance) printf("456");
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(pDerivedObj->meow_instance, al_get_default_mixer());
    //set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.0);
    al_set_sample_instance_gain(pDerivedObj->meow_instance, 0.6);

    pObj->pDerivedObj = pDerivedObj;
    printf("1546565");
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_monster1(monster1_L));
    _Register_elements(pObj, New_turret1(turret1_L));
    //_Register_elements(pObj, New_bullet1(bullet1_L));
    _Register_elements(pObj, New_diamond(diamond_L));
    _Register_elements(pObj, New_diamond2(diamond_L));
    _Register_elements(pObj, New_diamond3(diamond_L));
    _Register_elements(pObj, New_monster2(monster1_L));
    //_Register_elements(pObj, New_powerup(powerup_L));
    // setting derived object function
    pObj->scene_end = false;
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}

void game_scene_update(Scene *self)
{
    GameScene *gs = (GameScene *)self->pDerivedObj;

    if (key_state[ALLEGRO_KEY_ESCAPE]) {
        gs->pause = true;
        key_state[ALLEGRO_KEY_ESCAPE] = false; 
    }

    if (gs->pause) {
        ALLEGRO_MOUSE_STATE mouse_state;
        al_get_mouse_state(&mouse_state);

        //printf("Mouse X: %d, Y: %d\n", mouse_state.x, mouse_state.y);

        gs->on_continue = (mouse_state.x >= WIDTH / 2 - 225 && mouse_state.x <= WIDTH / 2 + 225 &&
                mouse_state.y >= HEIGHT / 2 - 75 && mouse_state.y <= HEIGHT / 2 + 15);

        gs->on_menu = (mouse_state.x >= WIDTH / 2 - 225 && mouse_state.x <= WIDTH / 2 + 225 &&                  
                       mouse_state.y >= HEIGHT / 2 + 75 && mouse_state.y <= HEIGHT / 2 + 165);

        if (mouse_state.buttons & 1) {
            if (gs->on_continue) {
                gs->pause = false; // Continue button
                //printf("Continue\n");
            } else if (gs->on_menu) {
                self->scene_end = true;
                window = 0; // Menu button
                //printf("Menu\n");
            }
        }
        return; 
    }

    if(level_one_finish){
        self->scene_end = true;
        window = 5;
    }

    ElementVec characters = _Get_label_elements(self, Character_L);
    for(int i = 0  ; i<characters.len ; i++){
        Character *chara = (Character *)(characters.arr[i]->pDerivedObj);
        if(chara->death){
            self->scene_end = true;
            window = 7; //death scene
            printf("dieeeee\n");
            return;
        }
    }

    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    double current_time = al_get_time();

    Elements *bullet = NULL;        
    bullet1 *bulletObj = NULL;     
    dir_bullet *dirbulletObj=NULL;
    trace_bullet *tracebulletObj=NULL;

    if (current_time - gs->shoot_time >= 4.0)
    {
        int bullet1_x = 800;
        int bullet1_y = 200;
        bullet = New_bullet1(bullet1_L);
        bulletObj = (bullet1 *)(bullet->pDerivedObj); // Cast to Bullet1*
        bullet1_set(bullet,bullet1_x,bullet1_y);
        //bulletObj->x = bullet1_x;
        //bulletObj->y = bullet1_y;
        _Register_elements(self, bullet);
        gs->shoot_time = current_time; // Update the timer
        int dir_bul_x=WIDTH;
        int dir_bul_y=800;
        int dx=-2;
        int dy=-2;
        bullet= New_dir_bullet(dir_bullet_L);
        dirbulletObj=(dir_bullet *)(bullet->pDerivedObj);
        dir_bullet_set(bullet,dir_bul_x,dir_bul_y);
        dirbulletObj->dx=dx;
        dirbulletObj->dy=dy;
        _Register_elements(self, bullet);
        int trace_bul_x=WIDTH;
        int trace_bul_y=800;
        bullet=New_trace_bullet(trace_bullet_L);
        dir_bullet_set(bullet,trace_bul_x,trace_bul_y);
        _Register_elements(self, bullet);

    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int k = 0; k < labelEle.len; k++)
            {
                ele->Interact(ele, labelEle.arr[k]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }
}

void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(gs->background, 0, 0, 0);
    al_draw_filled_rectangle(30, 50, 360, 166, al_map_rgba(0, 0, 0, 150));
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    if (gs->pause)
    {

        al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgba(0, 0, 0, 150)); // draw a transparent rectangle to make bg looks darker when pause
        
        int word_offset = 7;  
        double r = 45;  

        ALLEGRO_COLOR continue_color = gs->on_continue ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170); 
        ALLEGRO_COLOR menu_color = gs->on_menu ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);

        // continue button
        al_draw_filled_rounded_rectangle(WIDTH / 2 - 225, HEIGHT / 2 - 75, WIDTH / 2 + 225, HEIGHT / 2 + 15, r, r, continue_color);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 60 + word_offset, ALLEGRO_ALIGN_CENTRE, "Continue");

        // menu button
        al_draw_filled_rounded_rectangle(WIDTH / 2 - 225, HEIGHT / 2 + 75, WIDTH / 2 + 225, HEIGHT / 2 + 165, r, r, menu_color);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 90 + word_offset, ALLEGRO_ALIGN_CENTRE, "Menu");

    }
    
    double now_time = al_get_time() - start_time;
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 123, 110, ALLEGRO_ALIGN_CENTRE, "TIME :");
    char time_text[10001];
    sprintf(time_text, "%.1lf", now_time);
    level_one_log_time = now_time;
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 272, 110, ALLEGRO_ALIGN_CENTRE, time_text);

    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 150, 60, ALLEGRO_ALIGN_CENTRE, "SCORE :");
    char score_text[10001];
    sprintf(score_text, "%d", log_score);
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 300, 60, ALLEGRO_ALIGN_CENTRE, score_text);

    if(log_selected == 1){
        if(key_state[ALLEGRO_KEY_W]) {
            al_play_sample_instance(gs->meow_instance);
            printf("meowwwwwwwwwwww\n");
        }
    }

    al_play_sample_instance(gs->sample_instance);

}



void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font); 
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_sample(Obj->meow);
    al_destroy_sample_instance(Obj->meow_instance);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
