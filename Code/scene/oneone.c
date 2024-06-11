#include <allegro5/allegro_primitives.h>
#include "oneone.h"
#include <stdbool.h>

Scene *New_oneone(int label)
{
    oneone *pDerivedObj = (oneone *)malloc(sizeof(oneone));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 40, 0);

    //pDerivedObj->background = al_load_bitmap("assets/image/oneone_background.jpg");

    pDerivedObj->timer = al_get_time(); //time function

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = oneone_update;
    pObj->Draw = oneone_draw;
    pObj->Destroy = oneone_destroy;
    return pObj;
}

void oneone_update(Scene *self)
{
    oneone *Obj = (oneone *)(self->pDerivedObj);
    double current_time = al_get_time();

    if (current_time - Obj->timer >= 1.0) // second setting
    {
        self->scene_end = true;
        window = 1; // gamescene
    }
}

void oneone_draw(Scene *self)
{
    int word_offset = 24;

    oneone *Obj = ((oneone *)(self->pDerivedObj));
    // color of bg
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(Obj->font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 - word_offset, ALLEGRO_ALIGN_CENTRE, "Level 1-1");
}

void oneone_destroy(Scene *self)
{
    oneone *Obj = ((oneone *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    //al_destroy_bitmap(Obj->background);
    free(Obj);
    free(self);
}
