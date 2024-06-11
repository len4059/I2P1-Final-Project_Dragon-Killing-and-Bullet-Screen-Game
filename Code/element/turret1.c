#include "turret1.h"
#include "../shapes/Rectangle.h"
/*
   [turret1 function]
*/
Elements *New_turret1(int label)
{
    turret1 *pDerivedObj = (turret1 *)malloc(sizeof(turret1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/icon.jpg");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 660;
    pDerivedObj->y = 420;
    pDerivedObj->dir = 1;
    pDerivedObj->scale_factor = 0.7;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = turret1_update;
    pObj->Interact = turret1_interact;
    pObj->Draw = turret1_draw;
    pObj->Destroy = turret1_destroy;
    return pObj;
}
void turret1_update(Elements *self) {}
void turret1_interact(Elements *self, Elements *tar) {}
void turret1_draw(Elements *self)
{
    turret1 *Obj = ((turret1 *)(self->pDerivedObj));
    float scale_factor = Obj->scale_factor; 

    /*al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width * scale_factor,      
        Obj->height * scale_factor,  
        0                               
    );*/
}
void turret1_destroy(Elements *self)
{
    turret1 *Obj = ((turret1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
