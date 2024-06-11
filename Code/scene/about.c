#include <allegro5/allegro_primitives.h>
#include "about.h"
#include <stdbool.h>

Scene *New_about(int label)
{
    about *pDerivedObj = (about *)malloc(sizeof(about));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/about.mp3");

    pDerivedObj->background = al_load_bitmap("assets/image/about_background.jpg");

    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->back_x = 270;  
    pDerivedObj->back_y = 90;   
    pDerivedObj->direction_x = 270;  
    pDerivedObj->direction_y = 240;  

    pDerivedObj->on_back = false;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1.0); // set volumn
    
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = about_update;
    pObj->Draw = about_draw;
    pObj->Destroy = about_destroy;
    return pObj;
}

void about_update(Scene *self)
{
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);

    about *Obj = (about *)(self->pDerivedObj);

    Obj->on_back = (mouse_state.x >= Obj->back_x - 225 && mouse_state.x <= Obj->back_x + 225 &&
            mouse_state.y >= Obj->back_y - 45 && mouse_state.y <= Obj->back_y + 45);

    if (mouse_state.buttons & 1)
    {
        if (Obj->on_back)
        {
            self->scene_end = true;
            window = 0; 
        }
    }
    
    return;
}

void about_draw(Scene *self){

    int back_word_offset = 17;  
    int direction_word_offset = -190; 
    int y_offset = 80;
    double r = 45;  

    about *Obj = ((about *)(self->pDerivedObj));

    ALLEGRO_COLOR back_color = Obj->on_back ? al_map_rgb(240, 120, 120) : al_map_rgb(200, 120, 170);
    // draw bg
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, al_map_rgba(0, 0, 0, 60));

    // back button
    al_draw_filled_rounded_rectangle(Obj->back_x - 225, Obj->back_y - 45, Obj->back_x + 225, Obj->back_y + 45, r, r, back_color);
    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->back_x, Obj->back_y - back_word_offset, ALLEGRO_ALIGN_CENTRE, "BACK TO THE MENU");

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "1. Use 'A' and 'D' to move the character left and right");   

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + 80 + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "   and 'W' to jump.");   

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + 160 + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "2. Monsters and bullets can be killed"); 

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + 240 + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "    by jumping on their heads."); 

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + 320 + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "3. Try to finish the level as quickly as possible");

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + 400 + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "    or achieve the highest score.");

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->direction_x + direction_word_offset, Obj->direction_y + 480 + y_offset, ALLEGRO_ALIGN_LEFT, 
    
    "4. Press the space to cast a skill");

    al_play_sample_instance(Obj->sample_instance);
}

void about_destroy(Scene *self)
{
    about *Obj = ((about *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
