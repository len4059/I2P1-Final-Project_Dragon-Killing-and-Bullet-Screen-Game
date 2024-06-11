#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>

/*
   [Menu function]
*/
Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu.mp3");
    // load bg
    pDerivedObj->background = al_load_bitmap("assets/image/menu_background.png");
    // load title
    pDerivedObj->title = al_load_bitmap("assets/image/menu_title.png");

    pDerivedObj->knight = al_load_bitmap("assets/image/knight_menu.png");
    pDerivedObj->supercat = al_load_bitmap("assets/image/supercat_menu.png");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);

    int button_offset = 50;

    pDerivedObj->play_x = 500;
    pDerivedObj->play_y = HEIGHT / 2 + + 240 + button_offset;
    pDerivedObj->about_x = 1000;
    pDerivedObj->about_y = HEIGHT / 2 + 240 + button_offset;
    pDerivedObj->dress_x = 500;
    pDerivedObj->dress_y = HEIGHT / 2 + 360 + button_offset;
    pDerivedObj->exit_x = 1000;
    pDerivedObj->exit_y = HEIGHT / 2 + 360 + button_offset;

    pDerivedObj->on_play = false;
    pDerivedObj->on_about = false;
    pDerivedObj->on_dress = false;
    pDerivedObj->on_exit = false;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.0);  // Set volume
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}

void menu_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    Menu *Obj = (Menu *)(self->pDerivedObj);

    Obj->on_play = (mouse_state.x >= Obj->play_x - 225 && mouse_state.x <= Obj->play_x + 225 &&
                       mouse_state.y >= Obj->play_y - 45 && mouse_state.y <= Obj->play_y + 45);

    Obj->on_about = (mouse_state.x >= Obj->about_x - 225 && mouse_state.x <= Obj->about_x + 225 &&
                        mouse_state.y >= Obj->about_y - 45 && mouse_state.y <= Obj->about_y + 45);

    Obj->on_dress = (mouse_state.x >= Obj->dress_x - 225 && mouse_state.x <= Obj->dress_x + 225 &&
                        mouse_state.y >= Obj->dress_y - 45 && mouse_state.y <= Obj->dress_y + 45);

    Obj->on_exit = (mouse_state.x >= Obj->exit_x - 225 && mouse_state.x <= Obj->exit_x + 225 &&
                       mouse_state.y >= Obj->exit_y - 45 && mouse_state.y <= Obj->exit_y + 45);

    if (mouse_state.buttons & 1)
    {
        if (Obj->on_play){
            self->scene_end = true;
            window = 4; 
        }
        else if (Obj->on_about){
            self->scene_end = true;
            window = 2;
        }
        else if (Obj->on_dress){
            self->scene_end = true;
            window = 3;
        }
        else if (Obj->on_exit){
            self->scene_end = true;
            window = -1;
        }
    }
    return;
}

void menu_draw(Scene *self)
{
    int word_offset = 24;  
    double r = 45;  

    Menu *Obj = ((Menu *)(self->pDerivedObj));
    // picture of bg
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgba(0, 0, 0, 80));
    // picture of title
    al_draw_bitmap(Obj->title, 150, -120, 0);

    if(log_selected == 0 || log_selected == -1) al_draw_bitmap(Obj->knight, 500, 350, 0);
    else if(log_selected == 1) al_draw_bitmap(Obj->supercat, 500, 350, 0);

    ALLEGRO_COLOR play_color = Obj->on_play ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    ALLEGRO_COLOR about_color = Obj->on_about ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    ALLEGRO_COLOR dress_color = Obj->on_dress ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    ALLEGRO_COLOR exit_color = Obj->on_exit ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);

    // play button
    al_draw_filled_rounded_rectangle(Obj->play_x - 225, Obj->play_y - 45, Obj->play_x + 225, Obj->play_y + 45, r, r, play_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->play_x, Obj->play_y - word_offset, ALLEGRO_ALIGN_CENTRE, "PLAY");

    // about button
    al_draw_filled_rounded_rectangle(Obj->about_x - 225, Obj->about_y - 45, Obj->about_x + 225, Obj->about_y + 45, r, r, about_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->about_x, Obj->about_y - word_offset, ALLEGRO_ALIGN_CENTRE, "ABOUT");

    // dress button
    al_draw_filled_rounded_rectangle(Obj->dress_x - 225, Obj->dress_y - 45, Obj->dress_x + 225, Obj->dress_y + 45, r, r, dress_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->dress_x, Obj->dress_y - word_offset, ALLEGRO_ALIGN_CENTRE, "DRESS");

    // exit button
    al_draw_filled_rounded_rectangle(Obj->exit_x - 225, Obj->exit_y - 45, Obj->exit_x + 225, Obj->exit_y + 45, r, r, exit_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->exit_x, Obj->exit_y - word_offset, ALLEGRO_ALIGN_CENTRE, "EXIT");

    al_play_sample_instance(Obj->sample_instance);
}

void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
