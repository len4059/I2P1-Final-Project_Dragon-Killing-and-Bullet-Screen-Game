#include "global.h"
#include "shapes/Shape.h"
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1500; //1500/6=250
const int HEIGHT = 1008; //1008/6=168
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;