#include "dust.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
/*
   [dust function]
*/
Elements *New_dust(int label)
{
    dust *pDerivedObj = (dust *)malloc(sizeof(dust));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/dust.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 120;
    pDerivedObj->y = 180;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = dust_update;
    pObj->Interact = dust_interact;
    pObj->Draw = dust_draw;
    pObj->Destroy = dust_destroy;
    return pObj;
}
void dust_update(Elements *self) {}
void dust_interact(Elements *self, Elements *tar) {}
void dust_draw(Elements *self)
{
    dust *Obj = ((dust *)(self->pDerivedObj));

    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width,      
        Obj->height,  
        0                               
    );
}
void dust_destroy(Elements *self)
{
    dust *Obj = ((dust *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
