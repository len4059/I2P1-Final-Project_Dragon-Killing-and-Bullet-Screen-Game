#include "hellfloor.h"
#include <stdio.h>
/*
   [floor function]
*/

Elements *New_HellFloor(int label)
{
    HellFloor *pDerivedObj = (HellFloor *)malloc(sizeof(HellFloor));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->floor_block = al_load_bitmap("assets/image/hell_floor.png");
    pDerivedObj->platform_block = al_load_bitmap("assets/image/hell_platform.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->floor_block);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->floor_block);
    _HellFloor_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = HellFloor_draw;
    pObj->Update = HellFloor_update;
    pObj->Interact = HellFloor_interact;
    pObj->Destroy = HellFloor_destroy;
    return pObj;
}

void _HellFloor_load_map(HellFloor *const floor)
{
    FILE *data;
    data = fopen("assets/map/hell_map.txt", "r");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            fscanf(data, "%d", &floor->map_data[i][j]);
        }
    }
    fclose(data);
}

void HellFloor_update(Elements *const ele)
{  
    return;
}

void HellFloor_interact(Elements *const self_ele, Elements *const ele)
{
    if (ele->label == Character_L)
    {
        Character *chara = (Character *)(ele->pDerivedObj);
        HellFloor *floor = (HellFloor *)(self_ele->pDerivedObj);
        printf("airborne:%d",chara->airborne);
        if (chara->x < 0 - chara->width / 2)
            chara->x = 0 - chara->width / 2;
        else if (chara->x > WIDTH - chara->width / 2)
            chara->x = WIDTH - chara->width / 2;

        int start_y = HEIGHT - 10 * floor->height;
        bool floor_test=false;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (floor->map_data[i][j] == 1 || floor->map_data[i][j] == 2)
                {
                    int block_x = floor->x + j * floor->width;
                    int block_y = start_y + i * floor->height;

                    if (chara->x + chara->width > block_x + 40 &&
                        chara->x < block_x + floor->width - 40 &&
                        chara->y + chara->height+chara->dy > block_y - 15 &&
                        chara->y + chara->height - chara->dy <= block_y + 15 && chara->dy>0)
                    {
                        _Character_update_position(ele,0,block_y -chara->height-chara->y);
                        //chara->y = block_y - chara->height;
                        chara->dy = 0;
                        chara->airborne = false;
                        floor_test=true;
                        break;
                    }
                }
                if(!floor_test){
                    chara->airborne=true;
                }
            }
        }
    }
}

void HellFloor_draw(Elements *const ele)
{
    HellFloor *Obj = ((HellFloor *)(ele->pDerivedObj));
    int start_y = HEIGHT - 10 * Obj->height; 
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (Obj->map_data[i][j] == 1){
                al_draw_bitmap(Obj->floor_block, Obj->x + j * Obj->width, start_y + i * Obj->height, 0);
            }
            else if(Obj->map_data[i][j] == 2){
                al_draw_bitmap(Obj->platform_block, Obj->x + j * Obj->width, start_y + i * Obj->height, 0);
            }
        }
    }
}

void HellFloor_destroy(Elements *const ele)
{
    HellFloor *Obj = ((HellFloor *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->floor_block);
    free(Obj);
    free(ele);
}