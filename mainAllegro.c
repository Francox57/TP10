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
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    int disAlto = 720;
    int disAncho = 720;
    float casillaAlto =  (disAlto/ALTO);
    float casillaAncho =  (disAlto/ANCHO);
    float lado = (disAncho/(float)ANCHO) < (disAlto/(float)ALTO) ? disAncho/(float)ANCHO : disAlto/(float)ALTO;
    ALLEGRO_DISPLAY* disp = al_create_display(disAlto, disAncho);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_SAMPLE* pew = al_load_sample("pew_pew-dknight556-1379997159.wav");
    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("HarvestDawn.ogg",2, 2048);
    must_init(pew, "pew"); 
    must_init(music, "music");


    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
    
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
    ALLEGRO_EVENT event;

    bool redraw = true; 
    bool cerrar = false;
    
    float offsetx = (disAncho - lado*ANCHO)/2;
    float offsety = (disAlto - lado*ALTO)/2;
    int dif = ANCHO > ALTO ? ANCHO-ALTO : ALTO-ANCHO;

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
            if(ANCHO >= ALTO){
            for (int i = 0; i <= ANCHO; i++){ // Recorre la matriz y grilla y se fija donde se toco y pone o mata una
                for (int j = 0; j <= ALTO; j++){
                    if (mousex < i*(lado) && mousey < (lado)*j+offsety && mousey > offsety && mousey<disAlto-offsety){
                            printf("%d\n",j-1);
                            printf("%d\n",i-1);
                        if (mat[j-1][i-1] == ' '){
                            mat[j-1][i-1] = '*';
                            
                            al_draw_filled_rectangle(lado*(i-1),lado*(j-1)+offsety,lado*(i-1)+lado, lado*(j-1)+lado+offsety,al_map_rgb(0,255,0));
                            al_play_sample(pew, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            j = (ANCHO+dif+1);
                            i = (ALTO+dif+1);
                        }else if(mat[j-1][i-1]  == '*'){
                            mat[j-1][i-1]  = ' ';
                            al_draw_filled_rectangle(lado*(i-1),lado*(j-1)+offsety,lado*(i-1)+lado, lado*(j-1)+lado+offsety,al_map_rgb(0,0,0));
                            al_play_sample(pew, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            j = (ANCHO+dif+1);
                            i = (ALTO+dif+1);
                        }
                        
                    }
                }
            }
            copiar(mat,matReferencia);
            redraw = true;  // muestra la imagen
        }
        else{
            for (int i = 0; i <= ANCHO; i++){ // Recorre la matriz y grilla y se fija donde se toco y pone o mata una
                for (int j = 0; j <= ALTO; j++){
                    printf("%f\n",mousex);
                    printf("%f\n",mousey); 
                    if (mousex > i*(lado)+offsetx && mousey > (lado)*j && mousex > offsetx && mousex<disAncho-offsetx){
                        if (mat[i][j] == ' '){
                            mat[i][j] = '*';
                            printf("%d\n",j);
                            printf("%d\n",i);
                            al_draw_filled_rectangle(lado*(j)+offsetx,lado*(i),lado*(j)+lado+offsetx, lado*(i)+lado,al_map_rgb(0,255,0));
                            al_play_sample(pew, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            j = (ANCHO+dif+1);
                            i = (ALTO+dif+1);
                        }else if(mat[j][i]  == '*'){
                            mat[j][i]  = ' ';
                            al_draw_filled_rectangle(lado*(i)+offsetx,lado*(j),lado*(i)+lado+offsetx, lado*(j)+lado,al_map_rgb(0,0,0));
                            al_play_sample(pew, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                            j = (ANCHO+dif+1);
                            i = (ALTO+dif+1);
                        }
                        
                    }
                }
            }
            copiar(mat,matReferencia);
            redraw = true; // muestra la imagen
        }
    }
        else if (event.type == ALLEGRO_EVENT_KEY_CHAR){
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER){
                generacion_allegro(mat,matReferencia);
                print_mat(mat);
                al_clear_to_color(al_map_rgb(0, 0, 0));
                if(ANCHO >= ALTO){
                for (int i = 0; i < ALTO; i++){ 
                    for (int j = 0; j < ANCHO; j++){
                        printf("%c|%d|%d|\n",mat[i][j],i,j);
                        if (mat[i][j] == '*'){            
                            al_draw_filled_rectangle(lado*(j)+offsetx,lado*(i)+offsety,lado*(j)+lado+offsetx, lado*(i)+lado+offsety,al_map_rgb(0,255,0));
                            al_draw_filled_rectangle(0,0,disAncho, offsety,al_map_rgb(0,0,0));
                            al_draw_filled_rectangle(0,disAlto-offsety,disAncho, disAlto,al_map_rgb(0,0,0));
                        }
                    }
                }
            }
            redraw = true; 
        }
    }
        
               

        if(redraw && al_is_event_queue_empty(queue))
        {   
            dibujar_filycol(disAlto,disAncho,lado);
            al_flip_display();
            redraw = false;
        }
    }

// KABOOM
    al_destroy_sample(pew);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_audio_stream(music);
    return 0;
}

