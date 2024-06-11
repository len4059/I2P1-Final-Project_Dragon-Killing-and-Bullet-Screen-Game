#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "about.h"
#include "dress.h"
#include "death.h"
#include "oneone.h"
#include "onetwo.h"
#include "gamescene2.h"
#include "allelements.h"
#include "ending.h"

Scene *scene = NULL;

void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
    case GameScene2_L:
        scene = New_GameScene2(GameScene2_L);
        break;
    case AboutScene_L:
        scene = New_about(AboutScene_L);
        break;
    case DressScene_L:
        scene = New_dress(DressScene_L);
        break;
    case One_One_L:
        scene = New_oneone(One_One_L);
        break;
    case DeathScene_L:
        scene = New_death(DeathScene_L);
        break;
    case One_Two_L:
        scene = New_onetwo(One_Two_L);
        break;
    case EndingScene_L:
        scene = New_ending(EndingScene_L);
        break;
    default:
        break;
    }
}