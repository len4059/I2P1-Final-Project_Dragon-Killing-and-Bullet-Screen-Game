#include "bullet1.h"
#include "../shapes/Rectangle.h"
/*
   [bullet1 function]
*/
Elements *New_bullet1(int label)
{
    bullet1 *pDerivedObj = (bullet1 *)malloc(sizeof(bullet1));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/bullet1.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->dir = -1;
    pDerivedObj->damage=1;
    pDerivedObj->scale_factor =0.4;
    pDerivedObj->changedwidth=pDerivedObj->width*pDerivedObj->scale_factor;
    pDerivedObj->changedheight=pDerivedObj->height*pDerivedObj->scale_factor;

    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,//+(pDerivedObj->width/3)*pDerivedObj->scale_factor,
                                        pDerivedObj->y,//+(pDerivedObj->height*2/5)*pDerivedObj->scale_factor,
                                        pDerivedObj->x +pDerivedObj->changedwidth,
                                        pDerivedObj->y +pDerivedObj->changedheight);
    
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = bullet1_update;
    pObj->Interact = bullet1_interact;
    pObj->Draw = bullet1_draw;
    pObj->Destroy = bullet1_destroy;
    return pObj;
}
void bullet1_set(Elements *const ele,int x,int y){
    _bullet1_update_position(ele,x,y);
}
void bullet1_update(Elements *self) {
    bullet1 *Obj = ((bullet1 *)(self->pDerivedObj));
    _bullet1_update_position(self,Obj->dir*4,0);
    if (Obj->x + Obj->width * Obj->scale_factor < 0) {
        self->dele = true;
    }
}
void _bullet1_update_position(Elements *const ele, int dx, int dy)
{
    bullet1 *bullet = ((bullet1 *)(ele->pDerivedObj));
    bullet->x += dx;
    bullet->y += dy;
    Shape *hitbox = bullet->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
} 
void bullet1_interact(Elements *self, Elements *tar) {}
void bullet1_draw(Elements *self)
{
    bullet1 *Obj = ((bullet1 *)(self->pDerivedObj));
    float scale_factor = Obj->scale_factor; 
    //printf("ycheck:%d %d aaaa\n",Obj->y,*Obj->hitbox->center_y);
    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->changedwidth,
        Obj->changedheight,
        (Obj->dir<0?ALLEGRO_FLIP_HORIZONTAL:0)                        
    );
    //al_draw_bitmap(Obj->img,Obj->x,Obj->y,0);
}
void bullet1_destroy(Elements *self)
{
    bullet1 *Obj = ((bullet1 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
