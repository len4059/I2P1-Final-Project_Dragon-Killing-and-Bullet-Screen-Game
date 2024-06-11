#include <stdio.h>
#include <allegro5/allegro.h>
#include "../algif5/src/algif.h"         //Our gif header file, set the path to your .h file
#define GAME_TERMINATE 666
typedef struct GIF GIF;
typedef double (*fptrTime)(GIF*, double) ;
typedef void (*fptrDestroy)(GIF*) ;
typedef struct GIF{
    double start_time;
    ALGIF_ANIMATION *gif;
    fptrTime time;
    fptrDestroy destroy;
}GIF;
double get_time(GIF* obj, double time) {
    if(obj->start_time == 0) obj->start_time = time;
    return time - obj->start_time;
}
void gif_destroy(GIF* obj) {
    algif_destroy_animation(obj->gif);
}
GIF* New_GIF(){
    GIF* obj = (GIF*)malloc(sizeof(GIF));
    obj->start_time = 0;
    obj->time = get_time;
    obj->destroy = gif_destroy;
    return obj;
}
GIF* obj;
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer = NULL;
const int width = 800;
const int height = 600;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_draw();
void game_destroy();

/*
    You can declare some variables here if it is useful for you.
*/
bool draw = false;
double start_time = 0;

int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();
    printf("Hello world!!!\n");

    while ( msg != GAME_TERMINATE ) {
        msg = game_run();
        if ( msg == GAME_TERMINATE )
            printf("See you, world\n");
    }
    game_destroy();
    return 0;
}


void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if ( !al_init() ) {
        show_err_msg(-1);
    }

    display = al_create_display(width, height);
    al_set_window_position(display, 0, 0);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1 / 30.0);
    if ( display == NULL ) {
        show_err_msg(-1);
    }
    /*
        TODO: Something need to be created, initialized and registered.
    */
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(display));
}

void game_begin() {
    // load the gif file
    obj = New_GIF();
    obj->gif = algif_load_animation("god.gif");
    al_start_timer(timer);
}

int process_event() {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    /*
        TODO: Process the mouse event.
        Seperate the processing fo click event and moving event is encouraged.
    */
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if(event.timer.source == timer)
            draw = true;
    }else if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            return GAME_TERMINATE;
    }
    return 0;
}
void game_draw(){
    /*
    The second argument of algif_get_bitmap is double, you need to know when it exactly start.
    If you just use al_get_time() as input the gif may not play from start.
    */
    ALLEGRO_BITMAP *frame = algif_get_bitmap( obj->gif, obj->time(obj, al_get_time()) );
    if (frame == NULL) return;
    // rescale the bitmap
    al_draw_scaled_bitmap(frame,
                          // the rescale position of the frame
                          0, 0,
                          // the width and height you want to rescale
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          // the position of result image
                          0, 0,
                          // the width and height of result image
                          al_get_display_width(display),
                          al_get_display_height(display), 0);
    al_flip_display();
}
int game_run() {
    int error = 0;
    if ( !al_is_event_queue_empty(event_queue) ) {
        error = process_event();
    }
    if(draw){
        game_draw();
        draw = false;
    }
    return error;
}
void game_destroy() {
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    obj->destroy(obj);
}

