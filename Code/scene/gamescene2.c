#include "gamescene2.h"
#include "../element/bullet1.h"
#include "../element/dir_bullet.h"
#include "../element/trace_bullet.h"
#include "../element/diamond.h"
#include "../element/boss.h"
#include "../element/monster1.h"
#include "../element/monster3.h"
#include "../element/monster4.h"
#include "../element/dust.h"
#include "../element/dust2.h"
#include "../element/powerup.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

/*
   [GameScene2 function]
*/

double level_two_start_time;
double level_two_log_time = 0.0;

Scene *New_GameScene2(int label)
{
    level_one_finish = false;
    level_two_start_time = al_get_time();
    level_two_log_time = 0.0;
    GameScene2 *pDerivedObj = (GameScene2 *)malloc(sizeof(GameScene2));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/hell_bg.jpg");
    pDerivedObj->shoot_time = 0; // Initialize the timer
    pDerivedObj->pause = false;  // Initialize pause status
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0); 
    pDerivedObj->frame=0;
    pDerivedObj->song = al_load_sample("assets/sound/gamescene2.mp3");
    pDerivedObj->meow = al_load_sample("assets/sound/meow.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->meow_instance = al_create_sample_instance(pDerivedObj->meow);

    pDerivedObj->on_continue = false;
    pDerivedObj->on_menu = false;

    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    if(pDerivedObj->sample_instance) printf("456");
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(pDerivedObj->meow_instance, al_get_default_mixer());
    //set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.0);
    al_set_sample_instance_gain(pDerivedObj->meow_instance, 0.6);

    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_HellFloor(HellFloor_L));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L));
    _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_monster1(monster1_L));
    _Register_elements(pObj, New_monster3(monster1_L));
    _Register_elements(pObj, New_monster4(monster1_L));
    _Register_elements(pObj, New_dust(diamond_L));
    _Register_elements(pObj, New_dust2(diamond_L));
    _Register_elements(pObj, New_turret1(turret1_L));
    //_Register_elements(pObj, New_bullet1(bullet1_L));
    //_Register_elements(pObj, New_diamond(diamond_L));
    _Register_elements(pObj, New_powerup(powerup_L));
    _Register_elements(pObj, New_boss(boss_L));
    // setting derived object function
    pObj->scene_end = false;
    pObj->Update = game_scene2_update;
    pObj->Draw = game_scene2_draw;
    pObj->Destroy = game_scene2_destroy;
    return pObj;
}

void game_scene2_update(Scene *self)
{
    GameScene2 *gs = (GameScene2 *)self->pDerivedObj;

    if (key_state[ALLEGRO_KEY_ESCAPE]) {
        gs->pause = !gs->pause;
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

    ElementVec characters = _Get_label_elements(self, Character_L);
    for(int i = 0  ; i<characters.len ; i++){
        Character *chara = (Character *)(characters.arr[i]->pDerivedObj);
        if(chara->death){
            self->scene_end = true;
            window = 7; //death scene
            //rintf("dieeeee\n");
            return;
        }
    }

    ElementVec bosses = _Get_label_elements(self, boss_L);
    for(int i = 0  ; i<bosses.len ; i++){
        boss *bos = (boss *)(bosses.arr[i]->pDerivedObj);
        //printf("Checking Boss Death Status: %d\n", bos->death);  
        if(bos->death){
            self->scene_end = true;
            window = 8; //ending scene
            //printf("Boss is dead\n");
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
    if (current_time - gs->shoot_time >= 5.0)
    {
        int bullet1_x = 1000;
        int bullet1_y = 800;
        bullet = New_bullet1(bullet1_L);
        bulletObj = (bullet1 *)(bullet->pDerivedObj); // Cast to Bullet1*
        bullet1_set(bullet,bullet1_x,bullet1_y);
        //bulletObj->x = bullet1_x;
        //bulletObj->y = bullet1_y;
        _Register_elements(self, bullet);
        gs->shoot_time = current_time; // Update the timer


        int dir_bul_x=1000;
        int dir_bul_y=800;
        int dx=-2;
        int dy=-2;
        bullet= New_dir_bullet(dir_bullet_L);
        dirbulletObj=(dir_bullet *)(bullet->pDerivedObj);
        dir_bullet_set(bullet,dir_bul_x,dir_bul_y);
        dirbulletObj->dx=dx;
        dirbulletObj->dy=dy;
        _Register_elements(self, bullet);


        int trace_bul_x=1300;
        int trace_bul_y=200;
        bullet=New_trace_bullet(trace_bullet_L);
        dir_bullet_set(bullet,trace_bul_x,trace_bul_y);
        _Register_elements(self, bullet);

    }
    gs->frame++;
    Character *chara = (Character *)(characters.arr[0]->pDerivedObj);
    boss *bos = (boss *)(bosses.arr[0]->pDerivedObj);
    float cx=(chara->x+chara->width/2);
    float cy=(chara->y+chara->height/2);
    float bcx=(bos->x+bos->width/2);
    float bcy=(bos->y+bos->height/2);
    if(gs->frame%(5*60)==0&&cx<800){
        for(int i=0;i<3;i++){
            int dir_bul_x=cx+(i-1)*80;
            int dir_bul_y=0;
            int dx=0;
            int dy=4;
            bullet= New_dir_bullet(dir_bullet_L);
            dirbulletObj=(dir_bullet *)(bullet->pDerivedObj);
            dir_bullet_set(bullet,dir_bul_x,dir_bul_y);
            dirbulletObj->dx=dx;
            dirbulletObj->dy=dy;
            _Register_elements(self, bullet);
        }
    }    
    if(gs->frame%(5*60)==180&&cy>200){
        for(int i=0;i<3;i++){
            int dir_bul_x=WIDTH-20;
            int dir_bul_y=cy+(i-1)*80;
            int dx=-4;
            int dy=0;
            bullet= New_dir_bullet(dir_bullet_L);
            dirbulletObj=(dir_bullet *)(bullet->pDerivedObj);
            dir_bullet_set(bullet,dir_bul_x,dir_bul_y);
            dirbulletObj->dx=dx;
            dirbulletObj->dy=dy;
            _Register_elements(self, bullet);
        }
    }
    if((gs->frame%(10*60)==0)){
        int trace_bul_x=bcx;
        int trace_bul_y=bcy;
        bullet=New_trace_bullet(trace_bullet_L);
        trace_bullet_set(bullet,trace_bul_x,trace_bul_y);
        _Register_elements(self, bullet);
    }
    if(gs->frame%(15*60)==0){
        for(int i=0;i<5;i++){
            int dir_bul_x=WIDTH/7*(i+1);
            int dir_bul_y=0;
            int dx=0;
            int dy=2;
            bullet= New_dir_bullet(dir_bullet_L);
            dirbulletObj=(dir_bullet *)(bullet->pDerivedObj);
            dir_bullet_set(bullet,dir_bul_x,dir_bul_y);
            dirbulletObj->dx=dx;
            dirbulletObj->dy=dy;
            _Register_elements(self, bullet);
        }
        for(int i=0;i<3;i++){
            int dir_bul_x=WIDTH;
            int dir_bul_y=HEIGHT/5*(i+1);
            int dx=-2;
            int dy=0;
            bullet= New_dir_bullet(dir_bullet_L);
            dirbulletObj=(dir_bullet *)(bullet->pDerivedObj);
            dir_bullet_set(bullet,dir_bul_x,dir_bul_y);
            dirbulletObj->dx=dx;
            dirbulletObj->dy=dy;
            _Register_elements(self, bullet);
        }
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

void game_scene2_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene2 *gs = ((GameScene2 *)(self->pDerivedObj));
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
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - 60 + word_offset, ALLEGRO_ALIGN_CENTRE, "continue");

        // menu button
        al_draw_filled_rounded_rectangle(WIDTH / 2 - 225, HEIGHT / 2 + 75, WIDTH / 2 + 225, HEIGHT / 2 + 165, r, r, menu_color);
        al_draw_text(gs->font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 90 + word_offset, ALLEGRO_ALIGN_CENTRE, "menu");
    }
    

    double now_time = al_get_time() - level_two_start_time;
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 123, 110, ALLEGRO_ALIGN_CENTRE, "TIME :");
    char time_text[10001];
    sprintf(time_text, "%.1lf", now_time);
    level_two_log_time = now_time;
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 272, 110, ALLEGRO_ALIGN_CENTRE, time_text);
    
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 150, 50, ALLEGRO_ALIGN_CENTRE, "SCORE :");
    char score_text[10001];
    sprintf(score_text, "%d", log_score);
    al_draw_text(gs->font, al_map_rgb(255, 255, 255), 300, 50, ALLEGRO_ALIGN_CENTRE, score_text);

    if(log_selected == 1){
        if(key_state[ALLEGRO_KEY_W]) {
            al_play_sample_instance(gs->meow_instance);
            printf("meowwwwwwwwwwww\n");
        }
    }
    
    al_play_sample_instance(gs->sample_instance);
}

void game_scene2_destroy(Scene *self)
{
    GameScene2 *Obj = ((GameScene2 *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}