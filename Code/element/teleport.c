#include "teleport.h"
/*
   [teleport function]
*/

bool level_one_finish = false;

Elements *New_Teleport(int label)
{

    Teleport *pDerivedObj = (Teleport *)malloc(sizeof(Teleport));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/hell_portal.jpg");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 1300;
    pDerivedObj->y = 10;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Teleport_update;
    pObj->Interact = Teleport_interact;
    pObj->Draw = Teleport_draw;
    pObj->Destroy = Teleport_destory;
    return pObj;
}
void Teleport_update(Elements *const ele)
{
    Teleport *Obj = ((Teleport *)(ele->pDerivedObj));
    if (key_state[ALLEGRO_KEY_T])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}
void Teleport_interact(Elements *const self_ele, Elements *const ele)
{
    if (ele->label == Character_L)
    {
        Character *chara = (Character *)(ele->pDerivedObj);
        Teleport *Obj = (Teleport *)(self_ele->pDerivedObj);

        if (chara->x >= Obj->x -100 &&
            chara->x <= Obj->x + Obj->width &&
            chara->y >= Obj->y &&
            chara->y <= Obj->y + Obj->height &&
            Obj->activate){
            
            level_one_finish = true;
        }
    }   
}
void Teleport_draw(Elements *const ele)
{
    Teleport *Obj = ((Teleport *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Teleport_destory(Elements *const ele)
{
    Teleport *Obj = ((Teleport *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(ele);
}
