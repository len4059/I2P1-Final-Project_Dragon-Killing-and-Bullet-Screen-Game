#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "dress.h"

int log_selected = -1;

Scene *New_dress(int label)
{
    dress *pDerivedObj = (dress *)malloc(sizeof(dress));
    Scene *pObj = New_Scene(label);

    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
    
    pDerivedObj->knight = al_load_bitmap("assets/image/knight_select.png");
    pDerivedObj->supercat = al_load_bitmap("assets/image/supercat_select.png");

    pDerivedObj->background = al_load_bitmap("assets/image/address_bg.jpg");

    pDerivedObj->song = al_load_sample("assets/sound/dress.mp3");

    if (!pDerivedObj->song) {
        fprintf(stderr, "Failed to load sample!\n");
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }

    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.0); // Set volume 

    pDerivedObj->back_x = 240;
    pDerivedObj->back_y = 90;

    pDerivedObj->knight_x = WIDTH / 4 - al_get_bitmap_width(pDerivedObj->knight) / 2 + 180;
    pDerivedObj->knight_y = HEIGHT / 2 - al_get_bitmap_height(pDerivedObj->knight) / 2 + 50;
    pDerivedObj->supercat_x = WIDTH / 4 - al_get_bitmap_width(pDerivedObj->supercat) / 2 + 550;
    pDerivedObj->supercat_y = HEIGHT / 2 - al_get_bitmap_height(pDerivedObj->supercat) / 2 + 50;
    
    pDerivedObj->on_back = false;

    pDerivedObj->who_selected = log_selected; // -1,0 means choose knight(default), 1 means choose supercat

    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = dress_update;  
    pObj->Draw = dress_draw;
    pObj->Destroy = dress_destroy;
    return pObj;
}


void dress_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    dress *Obj = (dress *)(self->pDerivedObj);

    Obj->on_back = (mouse_state.x >= Obj->back_x - 225 && mouse_state.x <= Obj->back_x + 225 &&
            mouse_state.y >= Obj->back_y - 45 && mouse_state.y <= Obj->back_y + 45);

    if (mouse_state.buttons == 1)
    {
        if (Obj->on_back)
        {
            self->scene_end = true;
            window = 0; 
        }
        else if (mouse_state.x >= Obj->knight_x && mouse_state.x <= Obj->knight_x + al_get_bitmap_width(Obj->knight) &&
                 mouse_state.y >= Obj->knight_y && mouse_state.y <= Obj->knight_y + al_get_bitmap_height(Obj->knight))
        {
            Obj->who_selected = 0;
            printf("%d\n", Obj->who_selected);
        }
        else if (mouse_state.x >= Obj->supercat_x && mouse_state.x <= Obj->supercat_x + al_get_bitmap_width(Obj->supercat) &&
                 mouse_state.y >= Obj->supercat_y && mouse_state.y <= Obj->supercat_y + al_get_bitmap_height(Obj->supercat))
        {
            Obj->who_selected = 1;
            printf("%d\n", Obj->who_selected);
        }
        log_selected = Obj->who_selected;
    }
    return;
}

void dress_draw(Scene *self)
{
    int back_word_offset = 17;
    double r = 45;
    
    dress *Obj = (dress *)(self->pDerivedObj);

    ALLEGRO_COLOR back_color = Obj->on_back ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);

    al_draw_bitmap(Obj->background, 0, 0, 0);

    // back button
    al_draw_filled_rounded_rectangle(Obj->back_x - 225, Obj->back_y - 45, Obj->back_x + 225, Obj->back_y + 45, r, r, back_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->back_x, Obj->back_y - back_word_offset, ALLEGRO_ALIGN_CENTRE, "BACK TO THE MENU");

    al_draw_bitmap(Obj->knight, Obj->knight_x, Obj->knight_y, 0);
    al_draw_bitmap(Obj->supercat, Obj->supercat_x, Obj->supercat_y, 0);

    const char* text = "Select Your Character";
    if(Obj->who_selected == 0) text = "You Selected : KNIGHT !";
    else if(Obj->who_selected == 1) text = "You Selected : SUPERCAT !"; 
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), WIDTH / 2, HEIGHT - 70, ALLEGRO_ALIGN_CENTRE, text);

    al_play_sample_instance(Obj->sample_instance);
}

void dress_destroy(Scene *self)
{
    dress *Obj = (dress *)(self->pDerivedObj);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->knight);
    al_destroy_bitmap(Obj->supercat);
    free(Obj);
    free(self);
}
