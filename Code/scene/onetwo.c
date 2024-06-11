#include <allegro5/allegro_primitives.h>
#include "onetwo.h"
#include <stdbool.h>

Scene *New_onetwo(int label)
{
    onetwo *pDerivedObj = (onetwo *)malloc(sizeof(onetwo));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);

    //pDerivedObj->background = al_load_bitmap("assets/image/onetwo_background.jpg");

    pDerivedObj->timer = al_get_time(); //time function

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = onetwo_update;
    pObj->Draw = onetwo_draw;
    pObj->Destroy = onetwo_destroy;
    return pObj;
}

void onetwo_update(Scene *self)
{
    onetwo *Obj = (onetwo *)(self->pDerivedObj);
    double current_time = al_get_time();

    if (current_time - Obj->timer >= 1.0) // second setting
    {
        self->scene_end = true;
        window = 6; // gamescene2
    }
}

void onetwo_draw(Scene *self)
{
    int word_offset = 24;

    onetwo *Obj = ((onetwo *)(self->pDerivedObj));
    // color of bg
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - word_offset, ALLEGRO_ALIGN_CENTRE, "Level 1-2");
}

void onetwo_destroy(Scene *self)
{
    onetwo *Obj = ((onetwo *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    //al_destroy_bitmap(Obj->background);
    free(Obj);
    free(self);
}
