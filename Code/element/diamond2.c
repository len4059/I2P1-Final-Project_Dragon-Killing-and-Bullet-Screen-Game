#include "diamond2.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
/*
   [diamond2 function]
*/
Elements *New_diamond2(int label)
{
    diamond2 *pDerivedObj = (diamond2 *)malloc(sizeof(diamond2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/diamond.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 20;
    pDerivedObj->y = 630;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = diamond2_update;
    pObj->Interact = diamond2_interact;
    pObj->Draw = diamond2_draw;
    pObj->Destroy = diamond2_destroy;
    return pObj;
}
void diamond2_update(Elements *self) {}
void diamond2_interact(Elements *self, Elements *tar) {}
void diamond2_draw(Elements *self)
{
    diamond2 *Obj = ((diamond2 *)(self->pDerivedObj));

    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width,      
        Obj->height,  
        0                               
    );
}
void diamond2_destroy(Elements *self)
{
    diamond2 *Obj = ((diamond2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
