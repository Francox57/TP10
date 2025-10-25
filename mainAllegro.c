#include "header.h"
void must_init(bool test, const char *descrpcion);
void dibujar_filycol(int dispAlto, int dispAncho);

int main(int argc, char const *argv[])
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "imagen");
    must_init(al_init_primitives_addon(), "primitivas");
    must_init(al_install_mouse(), "mouse");

    int disAlto = 1000;
    int disAncho = 1000;
    
    ALLEGRO_DISPLAY* disp = al_create_display(disAlto, disAncho);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();


    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source()); 

    ALLEGRO_EVENT event;

    bool redraw = true; 
    bool cerrar = false;
    

    al_start_timer(timer);

    while(!cerrar)
    {
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }else if((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){
            cerrar = true;}
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){ 
            float mousex = event.mouse.x;
            float mousey = event.mouse.y;
            
            for (int i = 0; i <= ALTO; i++){
                for (int j = 0; j <= ANCHO; j++){
                    if (mousex < i*(disAncho/ANCHO) && mousey < (disAlto/ALTO)*j){
                        al_draw_filled_rectangle( (disAlto/ALTO)*(i-1),(disAncho/ANCHO)*(j-1),((disAlto/ALTO)*(i-1))+(disAlto/ALTO), ((disAncho/ANCHO)*(j-1))+((disAncho/ANCHO)),al_map_rgb(0,255,0));
                        
                        j = (ANCHO+1);
                        i = (ALTO+1);
                    }
                }
            }
            

            
            al_flip_display();
        }       

        if(redraw && al_is_event_queue_empty(queue))
        {
            dibujar_filycol(disAlto,disAncho);
            al_flip_display();

            redraw = false;
        }
    }


    // KABOOM //
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}

void must_init(bool test, const char *descripcion)
{
    if(test) return;

    printf("No se pudo inicializar %s\n", descripcion);
    exit(1);
}

void dibujar_filycol(int dispAlto, int dispAncho){
    int i;
    for (i = 0; i < ANCHO; i++){
        al_draw_line((dispAncho/ANCHO)*i,0, (dispAncho/ANCHO)*i, dispAlto, al_map_rgb(255, 0, 0), 0);
    }
    for (i = 0; i < ALTO; i++){
        al_draw_line(0,(dispAlto/ALTO)*i, dispAncho, (dispAlto/ALTO)*i, al_map_rgb(255, 0, 0), 0);
    }
    
    
}