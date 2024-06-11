#include "trace_bullet.h"
#include "../shapes/Circle.h"
#include <math.h>
/*
   [trace_bullet function]
*/
Elements *New_trace_bullet(int label)
{
    trace_bullet *pDerivedObj = (trace_bullet *)malloc(sizeof(trace_bullet));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/dir_bullet.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    pDerivedObj->dx=0;
    pDerivedObj->dy=0;
    pDerivedObj->dir = -1;
    pDerivedObj->damage=1;
    pDerivedObj->scale_factor =0.4;
    pDerivedObj->speed=3;
    pDerivedObj->changedwidth=pDerivedObj->width*pDerivedObj->scale_factor;
    pDerivedObj->changedheight=pDerivedObj->height*pDerivedObj->scale_factor;
    pObj->inter_obj[pObj->inter_len++] = Character_L;

    pDerivedObj->hitbox = New_Circle(pDerivedObj->x+27.5*pDerivedObj->scale_factor,//+(pDerivedObj->width/3)*pDerivedObj->scale_factor,
                                        pDerivedObj->y+27.5*pDerivedObj->scale_factor,//+(pDerivedObj->height*2/5)*pDerivedObj->scale_factor,
                                        27.5*pDerivedObj->scale_factor);
    
    // setting derived object functionㄉ
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = trace_bullet_update;
    pObj->Interact = trace_bullet_interact;
    pObj->Draw = trace_bullet_draw;
    pObj->Destroy = trace_bullet_destroy;
    return pObj;
}
void trace_bullet_set(Elements *const ele,int x,int y){
    _trace_bullet_update_position(ele,x,y);
}
void trace_bullet_update(Elements *self) {
    trace_bullet *Obj = ((trace_bullet *)(self->pDerivedObj));
    _trace_bullet_update_position(self,Obj->dx,Obj->dy);
    if (Obj->x + Obj->width * Obj->scale_factor < 0) {
        self->dele = true;
    }
}
void _trace_bullet_update_position(Elements *const ele, int dx, int dy)
{
    trace_bullet *bullet = ((trace_bullet *)(ele->pDerivedObj));
    bullet->x += dx;
    bullet->y += dy;
    Shape *hitbox = bullet->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
} 
void trace_bullet_interact(Elements *self, Elements *tar) {
    if(tar->label==Character_L){
        Character *chara= ((Character *)(tar->pDerivedObj));
        trace_bullet *bul=((trace_bullet *)(self->pDerivedObj));
        float center_x= chara->x+chara->width/2;
        float center_y= chara->y+chara->height/2;
        float xdir = center_x-bul->x;
        float ydir = center_y-bul->y;
        double dist= sqrt(xdir*xdir+ydir*ydir);
        bul->dx = xdir*bul->speed/dist;
        bul->dy = ydir*bul->speed/dist;
    }
    
}
void trace_bullet_draw(Elements *self)
{

    trace_bullet *Obj = ((trace_bullet *)(self->pDerivedObj));
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
void trace_bullet_destroy(Elements *self)
{
    trace_bullet *Obj = ((trace_bullet *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
