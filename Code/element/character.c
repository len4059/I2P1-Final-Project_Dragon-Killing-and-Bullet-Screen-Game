#include "character.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "boss.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include "powerup.h"
/*
   [Character function]
*/

Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    
    // setting derived object member
    // load character images

    char state_string[3][10] = {"stop", "move", "attack"};
    if(log_selected == -1 || log_selected == 0){
        for (int i = 0; i < 3; i++){
            char buffer[50];
            sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
            pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
        }
    }

    else if(log_selected == 1){
        for (int i = 0; i < 3; i++){
            char buffer[50];
            sprintf(buffer, "assets/image/supercat_%s.gif", state_string[i]);
            pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
        }
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());
    pDerivedObj->healthbar=al_load_bitmap("assets/image/healthbar.png");
    pDerivedObj->hpw = al_get_bitmap_width(pDerivedObj->healthbar);
    pDerivedObj->hph = al_get_bitmap_height(pDerivedObj->healthbar);
    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->airborne=false;
    pDerivedObj->x = 50;
    pDerivedObj->y = HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->inity=HEIGHT - pDerivedObj->height - 60;
    pDerivedObj->dx=0;
    pDerivedObj->dy=0;
    pDerivedObj->hp=12;
    pDerivedObj->maxhp=12;
    pDerivedObj->iframe=0;
    pDerivedObj->dashframe=0;
    pDerivedObj->pushbackframe = 0;
    pDerivedObj->shootcount=10;
    pDerivedObj->death=false;
    pDerivedObj->invincible=false;//
    pDerivedObj->score = 0;
    pObj->inter_obj[pObj->inter_len++] = monster1_L;
    pObj->inter_obj[pObj->inter_len++] = bullet1_L;
    pObj->inter_obj[pObj->inter_len++] = dir_bullet_L;
    pObj->inter_obj[pObj->inter_len++] = trace_bullet_L;
    pObj->inter_obj[pObj->inter_len++] = diamond_L;
    pObj->inter_obj[pObj->inter_len++] = boss_L;
    pObj->inter_obj[pObj->inter_len++] = powerup_L;    

    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_death(Elements *const ele){
    Character *chara = ((Character *)(ele->pDerivedObj));
    chara->death=true;
}
void Character_update(Elements *const ele)
{
    // use the idea of finite state machine to deal with different state
    Character *chara = ((Character *)(ele->pDerivedObj));
    if(chara->iframe>0){
        chara->iframe--; 
    }
    if(key_state[ALLEGRO_KEY_1]){
        Character_setinvincible(ele, true);
    } else if(key_state[ALLEGRO_KEY_2]){
        Character_setinvincible(ele, false);
    } else if(key_state[ALLEGRO_KEY_3]){
        chara->hp = 3;
    }
    if (chara->state == STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            if(log_selected == 0 || log_selected == -1){
                if(chara->shootcount > 0){
                    chara->state = ATK;
                    chara->shootcount--;
                }
            }
            else if(log_selected == 1){
                chara->state = ATK;
            }
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_W])
        {
            if(!chara->airborne){
                //  chara->state=JUMP;
                chara->dy = -30;
                chara->airborne = true;
            }
        }
        else
        {
            chara->state = STOP;
        }
    }
    else if (chara->state == MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Character_update_position(ele, -8, 0);
            chara->state = MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Character_update_position(ele, 8, 0);
            chara->state = MOVE;
        }
        if (key_state[ALLEGRO_KEY_W])
        {
            printf("trying:%d", chara->airborne);
            if(!chara->airborne){
                //chara->state=JUMP;
                chara->dy = -30;
                _Character_update_position(ele, 0, -15);
                chara->airborne = true;
            }
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = STOP;
    }
    else if (chara->state == ATK)
    {
        if(log_selected == 0 || log_selected == -1){
            if (chara->gif_status[chara->state]->done) {
                chara->state = STOP;
                chara->new_proj = false;
            }
            if (chara->gif_status[ATK]->display_index == 2 && !chara->new_proj)
            {
                if (chara->dir)
                {
                    _Register_elements(scene,
                        New_Projectile(
                            Projectile_L,
                            chara->x + chara->width - 100,
                            chara->y - 10,
                            5
                        )
                    );
                }
                else
                {
                    _Register_elements(scene,
                        New_Projectile(
                            Projectile_L,
                            chara->x + chara->width - 100,
                            chara->y + 10,
                            5
                        )
                    );
                }
                chara->new_proj = true;
            }
        }else if(log_selected==1){
            chara->dashframe=25;
            chara->state = STOP;
            chara->dx=25*(chara->dir?1:-1);
        }
    }

    if(chara->dashframe > 0){
        if(chara->dashframe < 5 && chara->pushbackframe == 0){
            chara->dx = 15;
        }
        chara->dashframe--;
        printf("dashing:%d\n", chara->dashframe);
    }else if(chara->pushbackframe>0){
        chara->dx=-(chara->pushbackframe*5);
        printf("pushing:%d\n",chara->pushbackframe);
        chara->pushbackframe--;
    }else{
        chara->dx=0;
    }

    _Character_update_position(ele, chara->dx, chara->dy);

    if(chara->airborne){
        if(chara->inity < chara->y){
            chara->dy = 0;
            _Character_update_position(ele, 0, chara->y - chara->inity);
            chara->airborne = false;
        } else {
            chara->dy += 2;
        }
        printf("jumpvel:%d\n", chara->dy);
    }
}

void Character_damage(Elements *const self,int damage){
    Character *chara = ((Character *)(self->pDerivedObj));
    if(!chara->invincible){
        chara->hp-=damage;
        chara->iframe=60;
        printf("hp:%d\n",chara->hp);
        if(chara->hp<0){
            Character_death(self);
        }
    }
}
void Character_draw(Elements *const ele)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(ele->pDerivedObj));
    if(chara->hp>0){
        al_draw_scaled_bitmap
        (chara->healthbar,0,0,
        chara->hpw,chara->hph,chara->x-20,chara->y-30, //hpbar draw position
        chara->hpw*chara->hp/chara->maxhp //hp caculation
        ,chara->hph,0);
    }
    if (chara->death){
        return;
    }
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2 && (log_selected == 0 || log_selected == -1))
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Character_setinvincible(Elements *const self,bool set){
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->invincible=set;
}
void Character_destory(Elements *const ele)
{
    Character *Obj = ((Character *)(ele->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _Character_update_position(Elements *const ele, int dx, int dy)           
{
    Character *chara = ((Character *)(ele->pDerivedObj));
    if(chara->x+dx<0){
        dx=-chara->x;
    }
    else if(chara->x+dx>WIDTH){
        dx=WIDTH-chara->x;

    }
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *const self, Elements *const target) {
    if(target->label==monster1_L){
        
        monster1 *mon = ((monster1 *)(target->pDerivedObj));

        Character *cha = ((Character *)(self->pDerivedObj));
        if (!mon->death&&mon->hitbox->overlap(mon->hitbox, cha->hitbox)&&!cha->death){
            if(cha->dy>0||cha->dashframe>0){
                mon->death=true;
                cha->dashframe=0;
                if(cha->dy>0){
                    cha->score += 3;
                    log_score += cha->score;
                    cha->score = 0;
                    cha->dy=-23;
                }
            }else{
                //printf("AHHHHHHHHHHH\n");
                if(!cha->iframe){
                    Character_damage(self,mon->damage);
                }
            }
        }

    }else if(target->label==bullet1_L){
        Character *cha = ((Character *)(self->pDerivedObj));
        bullet1 *bullet=((bullet1 *)(target->pDerivedObj));
        //printf("istouching:%d\n",bullet->hitbox->overlap(bullet->hitbox, cha->hitbox));
        //printf("x%d,y%d,w%d,h%d",bullet->x,bullet->y,bullet->changedwidth,bullet->changedheight);
        if (bullet->hitbox->overlap(bullet->hitbox, cha->hitbox)&&!cha->death){

            if(cha->dy>0){
                cha->score += 5;
                log_score += cha->score;
                cha->score = 0;
                target->dele=true;
                cha->dy=-23;
            }else{
                if(!cha->iframe){
                    Character_damage(self,bullet->damage);
                    target->dele=true;
                }
            }
        }
    }else if(target->label==dir_bullet_L){
        Character *cha = ((Character *)(self->pDerivedObj));
        dir_bullet *bullet=((dir_bullet *)(target->pDerivedObj));
        //printf("istouching:%d\n",bullet->hitbox->overlap(bullet->hitbox, cha->hitbox));
        //printf("x%d,y%d,w%d,h%d",bullet->x,bullet->y,bullet->changedwidth,bullet->changedheight);
        if (bullet->hitbox->overlap(bullet->hitbox, cha->hitbox)&&!cha->death){

            if(cha->dy>0){
                cha->score += 5;
                log_score += cha->score;
                cha->score = 0;
                target->dele=true;
                cha->dy=-23;
            }else{
                if(!cha->iframe){
                    Character_damage(self,bullet->damage);
                    target->dele=true;

                }
            }
        }
    }else if(target->label==trace_bullet_L){
        Character *cha = ((Character *)(self->pDerivedObj));
        trace_bullet *bullet=((trace_bullet *)(target->pDerivedObj));
        //printf("istouching:%d\n",bullet->hitbox->overlap(bullet->hitbox, cha->hitbox));
        //printf("x%d,y%d,w%d,h%d",bullet->x,bullet->y,bullet->changedwidth,bullet->changedheight);
        if (bullet->hitbox->overlap(bullet->hitbox, cha->hitbox)&&!cha->death){
            if(cha->dy>0){
                target->dele=true;
                cha->dy=-23;
                cha->score += 5;
                log_score += cha->score;
                cha->score = 0;
            }else{
                if(!cha->iframe){
                    Character_damage(self,bullet->damage);


                }
                target->dele=true;
            }
        }
    }else if(target->label==diamond_L){
        Character *cha = ((Character *)(self->pDerivedObj));
        diamond *dia=((diamond *)(target->pDerivedObj));
        if (dia->hitbox->overlap(dia->hitbox, cha->hitbox)&&!cha->death){
            cha->score+=7;
            log_score += cha->score;
            cha->score = 0;
            target->dele=true;
        }
    }else if(target->label==powerup_L){
        Character *cha = ((Character *)(self->pDerivedObj));
        powerup *power=((powerup *)(target->pDerivedObj));
        if (power->hitbox->overlap(power->hitbox, cha->hitbox)&&!cha->death){
            cha->iframe=600;
            target->dele=true;
        }
    }else if(target->label==boss_L){
        Character *cha = ((Character *)(self->pDerivedObj));
        boss *bos=((boss *)(target->pDerivedObj));
        if (!bos->death&&bos->hitbox->overlap(bos->hitbox, cha->hitbox)&&!cha->death){
            if(cha->dy>0||cha->dashframe>0){
                bos->hp-=1;
                cha->pushbackframe=14; 
                cha->iframe=25;
                cha->dx=0;
                if(bos->hp<0){
                    boss_death(target);
                }
                if(cha->dy>0){
                    cha->dy=-23;
                }
                cha->dashframe=0;
            }else{
                //printf("AHHHHHHHHHHH\n");
                if(!cha->iframe){
                    Character_damage(self,bos->damage);
                }
            }
        }
    }
}
