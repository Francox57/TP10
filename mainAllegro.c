#include "header.h"
#include "funciones.c"


int main(int argc, char const *argv[])
{
    int mat [ALTO][ANCHO];
    int matReferencia[ALTO][ANCHO];
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "imagen");
    must_init(al_init_primitives_addon(), "primitivas");
    must_init(al_install_mouse(), "mouse");

    int disAlto = 720;
    int disAncho = 720;
    int casillaAlto = (int) (disAlto/ALTO);
    int casillaAncho = (int) (disAlto/ANCHO);
    ALLEGRO_DISPLAY* disp = al_create_display(disAlto, disAncho);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();


    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source()); 

    ALLEGRO_EVENT event;

    bool redraw = true; 
    bool cerrar = false;
    
    llenar_mat(mat);
    copiar(mat,matReferencia);
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
            
            for (int i = 0; i <= ALTO; i++){ // Recorre la matriz y grilla y se fija donde se toco y pone o mata una
                for (int j = 0; j <= ANCHO; j++){
                    if (mousex < i*(casillaAncho) && mousey < (casillaAlto)*j){
                        if (mat[i-1][j-1] == ' '){
                            mat[i-1][j-1] = '*';
                            al_draw_filled_rectangle(casillaAlto*(i-1),casillaAncho*(j-1),casillaAlto*(i-1)+casillaAlto, casillaAncho*(j-1)+casillaAncho,al_map_rgb(0,255,0));
                        }else{
                            mat[i-1][j-1] = ' ';
                            al_draw_filled_rectangle(casillaAlto*(i-1),casillaAncho*(j-1),casillaAlto*(i-1)+casillaAlto, casillaAncho*(j-1)+casillaAncho,al_map_rgb(0,0,0));
                        }
                        j = (ANCHO+1);
                        i = (ALTO+1);
                    }
                }
            }
            copiar(mat,matReferencia);
            al_flip_display(); // muestra la imagen
        }else if (event.type == ALLEGRO_EVENT_KEY_CHAR){
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                generacion_allegro(mat,matReferencia);

                for (int i = 0; i < ALTO; i++){ 
                    for (int j = 0; j < ANCHO; j++){
                        if (mat[i][j] == '*'){
                            al_draw_filled_rectangle(casillaAlto*(i),casillaAncho*(j),casillaAlto*(i)+casillaAlto, casillaAncho*(j)+casillaAncho,al_map_rgb(0,255,0));
                        }else{
                            al_draw_filled_rectangle(casillaAlto*(i),casillaAncho*(j),casillaAlto*(i)+casillaAlto, casillaAncho*(j)+casillaAncho,al_map_rgb(0,0,0));
                        }   
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



    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    return 0;
}

