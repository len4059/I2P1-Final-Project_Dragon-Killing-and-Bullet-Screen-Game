#include <allegro5/allegro_primitives.h>
#include "death.h"
#include <stdbool.h>

Scene *New_death(int label)
{
    death *pDerivedObj = (death *)malloc(sizeof(death));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/death.mp3");

    pDerivedObj->background = al_load_bitmap("assets/image/death_background.jpg");

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->restart_x = WIDTH / 2;
    pDerivedObj->restart_y = HEIGHT / 2 - 60 + 270;
    pDerivedObj->menu_x = WIDTH / 2;
    pDerivedObj->menu_y = HEIGHT / 2 + 60 + 270;

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
    pObj->Update = death_update;
    pObj->Draw = death_draw;
    pObj->Destroy = death_destroy;
    return pObj;
}

void death_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    death *Obj = (death *)(self->pDerivedObj);

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
    
    return;
}

void death_draw(Scene *self)
{
    ///printf("?????\n");
    int word_offset = 24;  
    double r = 45;  

    death *Obj = ((death *)(self->pDerivedObj));
    // pic of bg
    al_draw_bitmap(Obj->background, 0, 0, 0);

    ALLEGRO_COLOR restart_color = Obj->on_restart ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    ALLEGRO_COLOR menu_color = Obj->on_menu ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    
    // restart button
    al_draw_filled_rounded_rectangle(Obj->restart_x - 225, Obj->restart_y - 45, Obj->restart_x + 225, Obj->restart_y + 45, r, r, restart_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->restart_x, Obj->restart_y - word_offset, ALLEGRO_ALIGN_CENTRE, "RETRY");

    // menu button
    al_draw_filled_rounded_rectangle(Obj->menu_x - 225, Obj->menu_y - 45, Obj->menu_x + 225, Obj->menu_y + 45, r, r, menu_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->menu_x, Obj->menu_y - word_offset, ALLEGRO_ALIGN_CENTRE, "MENU");

    al_play_sample_instance(Obj->sample_instance);
}

void death_destroy(Scene *self)
{
    death *Obj = ((death *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->background);
    free(Obj);
    free(self);
}
