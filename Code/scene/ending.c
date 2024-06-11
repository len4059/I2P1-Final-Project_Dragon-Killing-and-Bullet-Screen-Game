#include <allegro5/allegro_primitives.h>
#include "ending.h"
#include <stdbool.h>
#include <limits.h>

int log_highest_score = 0;
double log_fastest_time = INT_MAX;;

Scene *New_ending(int label)
{
    ending *pDerivedObj = (ending *)malloc(sizeof(ending));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/ending.mp3");

    pDerivedObj->knight_background = al_load_bitmap("assets/image/ending_background_knight.png");
    pDerivedObj->supercat_background = al_load_bitmap("assets/image/ending_background_cat.png");
    pDerivedObj->scrolling = al_load_bitmap("assets/image/scrolling_pic.png");
    pDerivedObj->scrolling2 = al_load_bitmap("assets/image/scrolling_pic2.png");
    pDerivedObj->scrolling3 = al_load_bitmap("assets/image/scrolling_pic3.png");
    pDerivedObj->scrolling4 = al_load_bitmap("assets/image/scrolling_pic4.png");

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->restart_x = WIDTH / 2 -300;
    pDerivedObj->restart_y = HEIGHT / 2 + 60 + 270;
    pDerivedObj->menu_x = WIDTH / 2 + 300;
    pDerivedObj->menu_y = HEIGHT / 2 + 60 + 270;
    pDerivedObj->rolling_pic_y = 200.0;
    pDerivedObj->rolling_pic_y2 = 280.0;
    pDerivedObj->rolling_pic_y3 = 360.0;
    pDerivedObj->rolling_pic_y4 = 440.0;

    pDerivedObj->on_restart = false;
    pDerivedObj->on_menu = false;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    //set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.0);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = ending_update;
    pObj->Draw = ending_draw;
    pObj->Destroy = ending_destroy;
    return pObj;
}

void ending_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    ending *Obj = (ending *)(self->pDerivedObj);

    Obj->on_restart = (mouse_state.x >= Obj->restart_x - 225 && mouse_state.x <= Obj->restart_x + 225 &&
            mouse_state.y >= Obj->restart_y - 45 && mouse_state.y <= Obj->restart_y + 45);

    Obj->on_menu = (mouse_state.x >= Obj->menu_x - 225 && mouse_state.x <= Obj->menu_x + 225 &&
                 mouse_state.y >= Obj->menu_y - 45 && mouse_state.y <= Obj->menu_y + 45);

    if (mouse_state.buttons & 1)
    {
        if (Obj->on_restart)
        {
            self->scene_end = true;
            window = 4; // restart game
        }
        else if (Obj->on_menu)
        {
            self->scene_end = true;
            window = 0; // go to menu
        }
    }

    double y_end_pos = 125;
    double y_start_pos = 440;

    Obj->rolling_pic_y -= 1;
    Obj->rolling_pic_y2 -= 1;
    Obj->rolling_pic_y3 -= 1;
    Obj->rolling_pic_y4 -= 1;
    if(Obj->rolling_pic_y < y_end_pos) Obj->rolling_pic_y = y_start_pos;
    else if(Obj->rolling_pic_y2 < y_end_pos) Obj->rolling_pic_y2 = y_start_pos;
    else if(Obj->rolling_pic_y3 < y_end_pos) Obj->rolling_pic_y3 = y_start_pos;
    else if(Obj->rolling_pic_y4 < y_end_pos) Obj->rolling_pic_y4 = y_start_pos;
    
    return;
}

void ending_draw(Scene *self)
{
    ///printf("?????\n");
    int word_offset = 24;  
    double r = 45; 
    double x_start_pos = 1000;

    ending *Obj = ((ending *)(self->pDerivedObj));
    // pic of bg
    if(log_selected == -1 || log_selected == 0) al_draw_bitmap(Obj->knight_background, 0, 0, 0);
    else if(log_selected == 1) al_draw_bitmap(Obj->supercat_background, 0, 0, 0);

    log_highest_score = log_score > log_highest_score ? log_score : log_highest_score;
    char now_score[10001];
    sprintf(now_score, "%d", log_score);
    char highest[10001];
    sprintf(highest, "%d", log_highest_score);

    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 500, 120, ALLEGRO_ALIGN_CENTRE, now_score);
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 500, 245, ALLEGRO_ALIGN_CENTRE, highest);

    double total_time = level_one_log_time + level_two_log_time;

    log_fastest_time = total_time < log_fastest_time ? total_time : log_fastest_time;
    char now_time[10001];
    sprintf(now_time, "%.1lf", total_time);
    char fastest[10001];
    sprintf(fastest, "%.1lf", log_fastest_time);

    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 500, 395, ALLEGRO_ALIGN_CENTRE, now_time);
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 500, 518, ALLEGRO_ALIGN_CENTRE, fastest);

    ALLEGRO_COLOR restart_color = Obj->on_restart ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    ALLEGRO_COLOR menu_color = Obj->on_menu ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    
    // restart button
    al_draw_filled_rounded_rectangle(Obj->restart_x - 225, Obj->restart_y - 45, Obj->restart_x + 225, Obj->restart_y + 45, r, r, restart_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->restart_x, Obj->restart_y - word_offset, ALLEGRO_ALIGN_CENTRE, "RESTRAT");

    // menu button
    al_draw_filled_rounded_rectangle(Obj->menu_x - 225, Obj->menu_y - 45, Obj->menu_x + 225, Obj->menu_y + 45, r, r, menu_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->menu_x, Obj->menu_y - word_offset, ALLEGRO_ALIGN_CENTRE, "MENU");

    al_draw_bitmap(Obj->scrolling, x_start_pos, Obj->rolling_pic_y, 0);
    al_draw_bitmap(Obj->scrolling2, x_start_pos, Obj->rolling_pic_y2, 0);
    al_draw_bitmap(Obj->scrolling3, x_start_pos, Obj->rolling_pic_y3, 0);
    al_draw_bitmap(Obj->scrolling4, x_start_pos, Obj->rolling_pic_y4, 0);

    if(log_selected == 1) al_play_sample_instance(Obj->sample_instance);
}

void ending_destroy(Scene *self)
{
    ending *Obj = ((ending *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->knight_background);
    free(Obj);
    free(self);
}
