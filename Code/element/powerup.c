#include "powerup.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
/*
   [powerup function]
*/
Elements *New_powerup(int label)
{
    powerup *pDerivedObj = (powerup *)malloc(sizeof(powerup));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/powerup.png");
    printf("load fail\n");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 720;
    pDerivedObj->y = 400;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = powerup_update;
    pObj->Interact = powerup_interact;
    pObj->Draw = powerup_draw;
    pObj->Destroy = powerup_destroy;
    return pObj;
}
void powerup_update(Elements *self) {}
void powerup_interact(Elements *self, Elements *tar) {}
void powerup_draw(Elements *self)
{
    powerup *Obj = ((powerup *)(self->pDerivedObj));

    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width,      
        Obj->height,  
        0                               
    );
}
void powerup_destroy(Elements *self)
{
    powerup *Obj = ((powerup *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
