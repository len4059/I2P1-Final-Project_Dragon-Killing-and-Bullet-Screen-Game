#include "diamond.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
/*
   [diamond function]
*/
Elements *New_diamond(int label)
{
    diamond *pDerivedObj = (diamond *)malloc(sizeof(diamond));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/diamond.png");
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
    pObj->Update = diamond_update;
    pObj->Interact = diamond_interact;
    pObj->Draw = diamond_draw;
    pObj->Destroy = diamond_destroy;
    return pObj;
}
void diamond_update(Elements *self) {}
void diamond_interact(Elements *self, Elements *tar) {}
void diamond_draw(Elements *self)
{
    diamond *Obj = ((diamond *)(self->pDerivedObj));

    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width,      
        Obj->height,  
        0                               
    );
}
void diamond_destroy(Elements *self)
{
    diamond *Obj = ((diamond *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
