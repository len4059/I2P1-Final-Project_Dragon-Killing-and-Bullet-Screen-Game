#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    Menu_L = 0,
    GameScene_L,
    GameScene2_L,
    AboutScene_L,
    DressScene_L,
    DeathScene_L,
    One_One_L,
    One_Two_L,
    EndingScene_L
} SceneType;

void create_scene(SceneType);

#endif