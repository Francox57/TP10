#include "header.h"
#include "funciones.c"


int main()
{
    int mat [ALTO][ANCHO];
    int matReferencia[ALTO][ANCHO];

    // BLOQUE DE INICIALIZACION //
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_init_image_addon(), "imagen");
    must_init(al_init_primitives_addon(), "primitivas");
    must_init(al_install_mouse(), "mouse");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");
    must_init(al_init_ttf_addon(),"TTF");
    ////////////////////////////////

    // BLOQUE DE VARIABLES /////////////////
    int disAlto = 720;
    int disAncho = 720;
    ALLEGRO_DISPLAY* disp = al_create_display(disAncho, disAlto);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_SAMPLE* pew = al_load_sample("pew_pew-dknight556-1379997159.wav");
    ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("HarvestDawn.ogg",2, 2048);
    ALLEGRO_FONT* font = al_load_ttf_font("OpenSans.ttf",15,0);
    must_init(font,"font");
    must_init(pew, "pew"); 
    must_init(music, "music");
    bool redraw = true; 
    bool cerrar = false;
    bool inicio = false;
    int contador = 0;
    typedef struct 
    {
        char * nombre;
        ALLEGRO_COLOR color_texto;
        ALLEGRO_COLOR color_pantalla;
        ALLEGRO_COLOR color_lineas;
        ALLEGRO_COLOR color_casilleros;

    }THEMES;
    
    THEMES dark = {"Dark",al_map_rgb(255,255,255),al_map_rgb(0,0,0),al_map_rgb(192,192,192),al_map_rgb(204,204,0)};
    THEMES light = {"Light",al_map_rgb(0,0,0),al_map_rgb(255,255,255),al_map_rgb(192,192,192),al_map_rgb(0,102,204)};
    THEMES bluescreen = {"Blue Screen",al_map_rgb(255,255,255),al_map_rgb(102,102,255),al_map_rgb(192,192,192),al_map_rgb(255,255,255)};
    THEMES random = {"Random",al_map_rgb(rand() % 256,rand() % 256,rand() % 256),al_map_rgb(rand() % 256,rand() % 256,rand() % 256),al_map_rgb(rand() % 256,rand() % 256,rand() % 256),al_map_rgb(rand() % 256,rand() % 256,rand() % 256)};
    

    
    // SE INICIALIZAN LAS VARIABLES CORRESPONDIENTES
    ///////////////////////////////

    ///////////////////// BLOQUE DE REGISTRO DE EVENTOS ///////////////////////////
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
    al_set_audio_stream_playmode(music, ALLEGRO_PLAYMODE_LOOP);
    ALLEGRO_EVENT event;
    // INDICA AL PROGRAMA QUE EVENTOS PUEDEN PASAR //
    ////////////////////////////////////////////////////////////////////////////////
    
    

    llenar_mat(mat);
    copiar(mat,matReferencia);
    al_start_timer(timer);

    while(!cerrar)
    {   
        float lado = (disAncho/(float)ANCHO) < (disAlto/(float)ALTO) ? disAncho/(float)ANCHO : disAlto/(float)ALTO; // cuanto mide los lados de los cuadrados
        float offsetx = (disAncho - lado*ANCHO)/2; // Cuanto ocupa el espacio no utilizado en x
        float offsety = (disAlto - lado*ALTO)/2;   // Cuanto ocupa el espacio no utilizado en y
        THEMES themeslist[MAXTHEMES] = {dark,light,bluescreen,random};

        al_wait_for_event(queue, &event); // indica al programa que revise si hay eventos

        if(event.type == ALLEGRO_EVENT_TIMER){ // si el usuario no ingresa nada simplemente se redibuja el estado en el que estaba
            redraw = true;
        }
        else if((event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)){ // si se apreta la X de la ventana se cierra el programa
            cerrar = true;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){  // si el usuario hace click
            if(inicio){
                float mousex = event.mouse.x; // recibe la posicion en x de donde hizo click
                float mousey = event.mouse.y; // recibe la posicion en y de donde hizo click
                bool flag = false;
                for (int i = 0; i <= ANCHO && !flag; i++){ // Recorre la matriz y grilla y se fija donde se toco y pone o mata una
                    for (int j = 0; j <= ALTO && !flag; j++){
                        if (mousex < i*(lado)+offsetx && mousey < (lado)*j+offsety && mousey > offsety && mousey<disAlto-offsety && mousex > offsetx && mousex < disAncho-offsetx){ // Se fije en que casilla se toco y que cumpla que no toque los bordes negros si es que hay offset
                            if (mat[j-1][i-1] == ' '){ 
                                mat[j-1][i-1] = '*';  // Revive una celda           
                                al_draw_filled_rectangle(lado*(i-1)+offsetx,lado*(j-1)+offsety,lado*(i-1)+lado+offsetx, lado*(j-1)+lado+offsety,themeslist[contador].color_casilleros); // Dibuja celda viva
                                al_play_sample(pew, 0.35, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                flag = true;
                            }else if(mat[j-1][i-1]  == '*'){
                                mat[j-1][i-1]  = ' '; // Mata una celda           
                                al_draw_filled_rectangle(lado*(i-1)+offsetx,lado*(j-1)+offsety,lado*(i-1)+lado+offsetx, lado*(j-1)+lado+offsety,themeslist[contador].color_pantalla); // Dibuja celda muerta
                                al_play_sample(pew, 0.35, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                                flag = true;
                            }
                        }
                    }
                }
                copiar(mat,matReferencia);
                redraw = true; 
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_CHAR){
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && inicio){
                generacion_allegro(mat,matReferencia); // Calcula la generacion siguiente si se apreta ENTER
                al_clear_to_color(themeslist[contador].color_pantalla); // limpia el display
                for (int i = 0; i < ALTO; i++){ 
                    for (int j = 0; j < ANCHO; j++){
                        if (mat[i][j] == '*'){            
                            al_draw_filled_rectangle(lado*(j)+offsetx,lado*(i)+offsety,lado*(j)+lado+offsetx, lado*(i)+lado+offsety,themeslist[contador].color_casilleros); // Dibuja la celda viva si es que lo esta
                            al_draw_filled_rectangle(0,0,disAncho, offsety,themeslist[contador].color_pantalla); // Dibuja la celda muerta si es que lo esta
                        }
                    }
                }
            redraw = true; 
            }else if (event.keyboard.keycode == ALLEGRO_KEY_SPACE && !inicio){ // Si toca espacio se da inicio al programa
                inicio = true; 
                al_clear_to_color(themeslist[contador].color_pantalla);
            }else if ((event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_LEFT) && !inicio){
                if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT){
                    if (contador >= 0 && contador <= MAXTHEMES-1){
                        contador++;
                        
                        if (contador > MAXTHEMES-1)
                        {
                            contador = 0;
                        }
                    }
                }else{
                    if (contador >= 0 && contador <= MAXTHEMES-1){
                        contador--;
                        if (contador < 0)
                        {
                            contador = MAXTHEMES-1;
                        }
                    }
                }

                if (contador == MAXTHEMES-1){
                random.color_casilleros = al_map_rgb(rand()%256,rand()%256,rand()% 256);
                random.color_pantalla = al_map_rgb(rand()%256,rand()%256,rand()% 256);
                random.color_texto = al_map_rgb(rand()%256,rand()%256,rand()% 256);
                random.color_lineas = al_map_rgb(rand()%256,rand()%256,rand()% 256);
                }
                
                
            printf("%d",contador);
            al_clear_to_color(themeslist[contador].color_pantalla);    
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE){ // Si se toca escape se sale del programa
                cerrar = true;
            }
            
            
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES && event.mouse.dz != 0 && !inicio){ // Cambiar tamaño de pantalla
            if (event.mouse.dz>0){ // Se fija que el cambio del mouse scroll sea para arriba
                disAlto += 10;
                disAncho += 10;
                event.mouse.z = 0;
                redraw = true;      
            }else if (event.mouse.dz<0) // Se fija que el cambio del mouse scroll sea para abajo
            {
                disAlto -= 10;
                disAncho -= 10;
                event.mouse.z = 0;
                redraw = true;      
            }
            if (disAlto < 100){
                disAlto = 100;
            }
            if (disAncho < 100){
                disAncho = 100;
            }
            al_resize_display(disp,disAncho,disAlto); // Cambia tamaño de pantalla
            al_clear_to_color(themeslist[contador].color_pantalla);
        }
        
               

        if(redraw && al_is_event_queue_empty(queue))
        {   
            if(inicio){
            dibujar_filycol(disAlto,disAncho,lado,themeslist[contador].color_lineas); // Si se inicio el programa se dibuja las filas y columnas
            al_flip_display();
            redraw = false;
            }else{ // Si no se inicio el programa se pone el menu
                al_draw_multiline_textf(font,themeslist[contador].color_texto,disAncho/2,disAlto/8,disAncho-disAncho/3,20,ALLEGRO_ALIGN_CENTER,"Bienvenido al juego de la vida, para empezar presione ESPACIO, para pasar una generacion presione ENTER (se recomienda dejar apretado para un mejor efecto), haga click en las celdas que desee matar o resucitar, mouse scroll para cambiar tamaño de pantalla(solo en este menu)\n\nTema actual: %s",themeslist[contador].nombre);
                al_flip_display();
                redraw = false;
            }
        }
    }

// Destruye todo lo que se uso de allegro
    al_destroy_font(font);
    al_destroy_sample(pew);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_audio_stream(music);
    return 0;
}




/*
else if (event.type == ALLEGRO_EVENT_MOUSE_AXES && event.mouse.dz != 0){
            if (event.mouse.dz>0){
                disAlto += 10;
                disAncho += 10;
                event.mouse.z = 0;
                redraw = true;      
            }else if (event.mouse.dz<0)
            {
                disAlto -= 10;
                disAncho -= 10;
                
                event.mouse.z = 0;
                redraw = true;      
            }
            if (disAlto < 100){
                disAlto = 100;
            }
            if (disAncho < 100){
                disAncho = 100;
            }
            al_resize_display(disp,disAncho,disAlto);
            
            
        }
*/