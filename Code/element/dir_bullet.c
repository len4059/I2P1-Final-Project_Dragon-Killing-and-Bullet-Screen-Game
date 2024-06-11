#include "dir_bullet.h"
#include "../shapes/Circle.h"
/*
   [dir_bullet function]
*/
Elements *New_dir_bullet(int label)
{
    dir_bullet *pDerivedObj = (dir_bullet *)malloc(sizeof(dir_bullet));
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
    pDerivedObj->changedwidth=pDerivedObj->width*pDerivedObj->scale_factor;
    pDerivedObj->changedheight=pDerivedObj->height*pDerivedObj->scale_factor;

    pDerivedObj->hitbox = New_Circle(pDerivedObj->x+27.5*pDerivedObj->scale_factor,//+(pDerivedObj->width/3)*pDerivedObj->scale_factor,
                                        pDerivedObj->y+27.5*pDerivedObj->scale_factor,//+(pDerivedObj->height*2/5)*pDerivedObj->scale_factor,
                                        27.5*pDerivedObj->scale_factor);
    
    // setting derived object functionㄉ
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = dir_bullet_update;
    pObj->Interact = dir_bullet_interact;
    pObj->Draw = dir_bullet_draw;
    pObj->Destroy = dir_bullet_destroy;
    return pObj;
}
void dir_bullet_set(Elements *const ele,int x,int y){
    _dir_bullet_update_position(ele,x,y);
}
void dir_bullet_update(Elements *self) {
    dir_bullet *Obj = ((dir_bullet *)(self->pDerivedObj));
    _dir_bullet_update_position(self,Obj->dx,Obj->dy);
    if (Obj->x + Obj->width * Obj->scale_factor < 0) {
        self->dele = true;
    }
}
void _dir_bullet_update_position(Elements *const ele, int dx, int dy)
{
    dir_bullet *bullet = ((dir_bullet *)(ele->pDerivedObj));
    bullet->x += dx;
    bullet->y += dy;
    Shape *hitbox = bullet->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
} 
void dir_bullet_interact(Elements *self, Elements *tar) {

    
}
void dir_bullet_draw(Elements *self)
{

    dir_bullet *Obj = ((dir_bullet *)(self->pDerivedObj));
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
void dir_bullet_destroy(Elements *self)
{
    dir_bullet *Obj = ((dir_bullet *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
