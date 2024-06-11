#include "boss.h"
#include "../shapes/Rectangle.h"
/*
   [boss function]
*/

Elements *New_boss(int label)
{
    boss *pDerivedObj = (boss *)malloc(sizeof(boss));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/boss.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 1150;
    pDerivedObj->y = 45;
    pDerivedObj->dir = -1;
    pDerivedObj->x_pos_max = 1150;
    pDerivedObj->x_pos_min = 1150;
    pDerivedObj->death = false;
    pDerivedObj->damage = 1;
    pDerivedObj->scale_factor = 0.25;
    pDerivedObj->hp=7;
    
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;

    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width * pDerivedObj->scale_factor,
                                        pDerivedObj->y + pDerivedObj->height * pDerivedObj->scale_factor);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = boss_update;
    pObj->Interact = boss_interact;
    pObj->Draw = boss_draw;
    pObj->Destroy = boss_destory;
    return pObj;
}

void _boss_update_position(Elements *const ele, int dx, int dy)
{
    boss *mon = ((boss *)(ele->pDerivedObj));
    mon->x += dx;
    mon->y += dy;
    Shape *hitbox = mon->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void boss_death(Elements *self){
    boss *bos = ((boss *)(self->pDerivedObj));
    /*DO SOMETHING*/
    bos->death = true;
    //self->dele=true;
}
void boss_update(Elements *self) {
    boss *Obj = ((boss *)(self->pDerivedObj));
    /*
    _boss_update_position(self, Obj->dir * 2, 0);
    
    if (Obj->x <= Obj->x_pos_min) {
        Obj->x = Obj->x_pos_min;
        Obj->dir = 1;
    } else if (Obj->x + Obj->width * Obj->scale_factor >= Obj->x_pos_max) {
        Obj->x = Obj->x_pos_max - Obj->width * Obj->scale_factor;
        Obj->dir = -1;
    }*/
}

void boss_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L&&false) { // DISABLED
        boss *mon = ((boss *)(self->pDerivedObj));
        Character *cha = ((Character *)(tar->pDerivedObj));

        if (!mon->death && mon->hitbox->overlap(mon->hitbox, cha->hitbox) && !cha->death) {
            if (cha->dy > 0) {
                mon->hp--;
                if(mon->hp<0){
                    boss_death(self);
                }
                cha->dy = -13; 
            } 
        }
    }
    else if(tar->label==Projectile_L){
        boss *mon = ((boss *)(self->pDerivedObj));
        Projectile *project =((Projectile *)(tar->pDerivedObj));
            if (!mon->death && mon->hitbox->overlap(mon->hitbox, project->hitbox)) {
                 mon->hp--;
                if(mon->hp<0){
                    boss_death(self);
                }
                tar->dele=true;
            }
    }
}

void boss_draw(Elements *self)
{
    boss *Obj = ((boss *)(self->pDerivedObj));
    if (Obj->death) {
        return;
    }
    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width * Obj->scale_factor,      
        Obj->height * Obj->scale_factor,     
        (Obj->dir>0)?ALLEGRO_FLIP_HORIZONTAL:0
    );
}

void boss_destory(Elements *self)
{
    boss *Obj = ((boss *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

