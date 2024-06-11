#include "diamond3.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
/*
   [diamond3 function]
*/
Elements *New_diamond3(int label)
{
    diamond3 *pDerivedObj = (diamond3 *)malloc(sizeof(diamond3));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/diamond.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 1220;
    pDerivedObj->y = 405;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = diamond3_update;
    pObj->Interact = diamond3_interact;
    pObj->Draw = diamond3_draw;
    pObj->Destroy = diamond3_destroy;
    return pObj;
}
void diamond3_update(Elements *self) {}
void diamond3_interact(Elements *self, Elements *tar) {}
void diamond3_draw(Elements *self)
{
    diamond3 *Obj = ((diamond3 *)(self->pDerivedObj));

    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width,      
        Obj->height,  
        0                               
    );
}
void diamond3_destroy(Elements *self)
{
    diamond3 *Obj = ((diamond3 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
