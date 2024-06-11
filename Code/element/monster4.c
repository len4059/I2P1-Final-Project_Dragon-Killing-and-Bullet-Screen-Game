#include "monster4.h"
#include "../shapes/Rectangle.h"
/*
   [monster4 function]
*/
Elements *New_monster4(int label)
{
    monster4 *pDerivedObj = (monster4 *)malloc(sizeof(monster4));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/monster4.png");
    if (!pDerivedObj->img) {
        fprintf(stderr, "Failed to load monster4 image!\n");
        free(pDerivedObj);
        free(pObj);
        return NULL;
    }
    printf("556468456156\n");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 600;
    pDerivedObj->y = 350;
    pDerivedObj->dir = 1;
    pDerivedObj->x_pos_max = 850;
    pDerivedObj->x_pos_min = 500;
    pDerivedObj->death = false;
    pDerivedObj->damage = 1;
    pDerivedObj->scale_factor = 0.25;
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;

    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width * pDerivedObj->scale_factor,
                                        pDerivedObj->y + pDerivedObj->height * pDerivedObj->scale_factor);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = monster4_update;
    pObj->Interact = monster4_interact;
    pObj->Draw = monster4_draw;
    pObj->Destroy = monster4_destory;
    return pObj;
}

void _monster4_update_position(Elements *const ele, int dx, int dy)
{
    monster4 *mon = ((monster4 *)(ele->pDerivedObj));
    mon->x += dx;
    mon->y += dy;
    Shape *hitbox = mon->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void monster4_update(Elements *self) {
    monster4 *Obj = ((monster4 *)(self->pDerivedObj));
    _monster4_update_position(self, Obj->dir * 4, 0);
    if (Obj->x <= Obj->x_pos_min) {
        Obj->x = Obj->x_pos_min;
        Obj->dir = 1;
    } else if (Obj->x + Obj->width * Obj->scale_factor >= Obj->x_pos_max) {
        Obj->x = Obj->x_pos_max - Obj->width * Obj->scale_factor;
        Obj->dir = -1;
    }
}

void monster4_interact(Elements *self, Elements *tar) {
    if (tar->label == Character_L) {
        monster4 *mon = ((monster4 *)(self->pDerivedObj));
        Character *cha = ((Character *)(tar->pDerivedObj));

        if (!mon->death && mon->hitbox->overlap(mon->hitbox, cha->hitbox) && !cha->death) {
            if (cha->dy > 0) {
                mon->death = true;
                cha->dy = -13; 
            } 
        }
    }
    else if(tar->label==Projectile_L){
        monster4 *mon = ((monster4 *)(self->pDerivedObj));
        Projectile *project =((Projectile *)(tar->pDerivedObj));
            if (!mon->death && mon->hitbox->overlap(mon->hitbox, project->hitbox)) {
                mon->death=true;
                tar->dele=true;
            }
    }
}

void monster4_draw(Elements *self)
{
    //printf ("load successfully");
    monster4 *Obj = ((monster4 *)(self->pDerivedObj));
    if (Obj->death) {
        return;
    }
    al_draw_scaled_bitmap(
        Obj->img, 
        0, 0, Obj->width, Obj->height,  
        Obj->x, Obj->y,                 
        Obj->width * Obj->scale_factor,      
        Obj->height * Obj->scale_factor,     
        (Obj->dir > 0) ? ALLEGRO_FLIP_HORIZONTAL : 0
    );
}

void monster4_destory(Elements *self)
{
    monster4 *Obj = ((monster4 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

