#include "dust2.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
/*
   [dust2 function]
*/
Elements *New_dust2(int label)
{
    dust2 *pDerivedObj = (dust2 *)malloc(sizeof(dust2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/dust.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 1320;
    pDerivedObj->y = 630;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = dust2_update;
    pObj->Interact = dust2_interact;
    pObj->Draw = dust2_draw;
    pObj->Destroy = dust2_destroy;
    return pObj;
}
void dust2_update(Elements *self) {}
void dust2_interact(Elements *self, Elements *tar) {}
void dust2_draw(Elements *self)
{
    dust2 *Obj = ((dust2 *)(self->pDerivedObj));

    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width,      
        Obj->height,  
        0                               
    );
}
void dust2_destroy(Elements *self)
{
    dust2 *Obj = ((dust2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
