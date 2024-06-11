#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED
#include "../global.h"
#include "../element/element.h"

/*
   [scene object]
*/
typedef struct EPNode
{
    int id;
    Elements *ele;
    struct EPNode *next;
} EPNode;
typedef struct Element_vector
{
    Elements *arr[MAX_ELEMENT];
    int len;
} ElementVec;
typedef struct _Scene Scene;
typedef void (*fptrUpdate)(Scene *const);
typedef void (*fptrDraw)(Scene *const);
typedef void (*fptrDestroy)(Scene *const);
struct _Scene
{
    int label;
    void *pDerivedObj;
    bool scene_end;
    int ele_num;

    EPNode *ele_list[MAX_ELEMENT];
    // interface for function
    fptrUpdate Update;
    fptrDraw Draw;
    fptrDestroy Destroy;
};
Scene *New_Scene(int label);
void _Register_elements(Scene *const, Elements *);
void _Remove_elements(Scene *const, Elements *);
ElementVec _Get_all_elements(Scene *const);
ElementVec _Get_label_elements(Scene *const, int label);
#endif
