#include <stdio.h>
#include "header.h"

void llenar_mat (int mat[ALTO][ANCHO]){
    int i,j;//Valor de fila y columna
    for(i=0;i<ALTO;i++){//Llena la matriz con celulas muertas
        for(j=0;j<ANCHO;j++){
            mat[i][j] = ' '; 
        }
    }
}

void inicio(int mat [ALTO][ANCHO]){
    int i=0, j=0;//Inicializa vairable columna y fila
    while(i!=-1 && j!=-1){//Si no se presiona e 
        printf("Introducir valor de casilla (separar fila y columna con coma), para borrar seleccionar misma casilla\n");
        printf("Apretar e para empezar\n");
        i = numero (); //Cambia el getchar a int
        if(i>=0 && i<ALTO){//Si es valido el caracter ingresado
            j = numero();
            if(j>=0 && j<ANCHO){
                mat[i][j]= mat[i][j]=='*'? ' ': '*'; //Cambia el valor de la celda al contrario
                print_mat(mat);//imprime nueva matriz
            }
            else if (j<-1 || j>=ANCHO){
                printf("Ingresar valor valido\n");
            }
        }
        else if (i<-1 || i>=ALTO){
            printf("Ingresar valor valido\n");
        }
    }
    printf("Cuantas generaciones desea que pase? Para avanzar solo una generacion apretar enter.\n");
    printf("Para salir del programa apretar q\n");
}

void generacion( int mat[ALTO][ANCHO], int matReferencia[ALTO][ANCHO],int tiempo){
    int i, j;//Valor fila columna
    while(tiempo>0){
        for(i=0;i<ALTO;i++){
            for(j=0;j<ANCHO;j++){
                if (mat[i][j] == ' '){//Se fija si hay una celda muerta
                    nace(mat,matReferencia,i,j);//Manda a revisar si en ese espacio nace una celula
                }
            }
        }
        for(i=0;i<ALTO;i++){
            for(j=0;j<ANCHO;j++){
                if (mat[i][j] == '*'){//Se fija si hay una celda viva
                    muere(mat,matReferencia,i,j);//Manda a revisar si en ese espacio nace una celula
                }
            }
        }
        copiar(mat,matReferencia); //Se copia el lado de la matriz para luego hacer los calculos correspondientes        
        tiempo--;
    }
    print_mat(mat);
}

void nace (int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int i, int j){                     
    int copia [3][3];
    int vivas = 0; //Se inicializa el valor de celulas vivas en 0
    int k, c, l, t;//Valores de filas y columnas
    for(k=0,t=(i-1);k<3;k++, t++){//t = i-1 se esta creando una copia 3x3 al rededor de la celda muerta
        for(l=0,c=(j-1);l<3; l++,c++){
            if(t>=0 &&t<ALTO && c>=0 && c<ANCHO){//Se fija que el alrededor de la celda muerta este dentro de la matriz
                copia[k][l]=matReferencia[t][c];//Se copia matriz referencia para hacer los calculos de la matriz orginal
            }
            else{
                copia[k][l]= ' ';//Si la celda se encuentra en los bordes de la matriz llena las celdas inexistentes con puntos muertos
            }
        }
    }
    for(k=0;k<3;k++){
        for(l=0;l<3;l++){
            if(copia[k][l]=='*'){ //Si hay una celula viva se incrementa vivas
                vivas++;
            }   
        }
    }
    if(vivas==3){//Si es igual a 3 nace una nueva celula
        mat[i][j]= '*';
    }
}

void muere (int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO], int i, int j){
    int copia [3][3];
    int vivas = 0;//Se inicializa el valor de celulas vivas en 0
    int k, l, c, t;
    for(k=0,t=(i-1);k<3;k++, t++){//t = i-1 se esta creando una copia 3x3 al rededor de la celda muerta
        for(l=0,c=(j-1);l<3; l++,c++){//c = j-1 porque se esta creando 
            if(t>=0 &&t<ALTO && c>=0 && c<ANCHO){//Se fija que el alrededor de la celda muerta este dentro de la matriz
                copia[k][l]=matReferencia[t][c];//Se copia matriz referencia para hacer los calculos de la matriz orginal
            }
            else{
                copia[k][l]= ' ';//Si la celda se encuentra en los bordes de la matriz llena las celdas inexistentes con puntos muertos
            }
        }
    }
    for(k=0;k<3;k++){
        for(l=0;l<3;l++){
            if(copia[k][l]=='*'){//Si hay una celula viva se incrementa vivas
                    vivas++;
            }
        }
    }
    vivas-=1; //Se le resta uno para no contar la celula del medio
    if(vivas<2 || vivas>3){ //Si tiene menos de 2 o mas de 3 mata la celula
        mat[i][j]= ' ';
    }
}

void print_mat (int mat[ALTO][ANCHO]){ //Funcion para imprimir matriz
    int i,j;//Valor de fila y columna
    int cont = 0;//Inicio un contador que va a tener el valor de los indices en 0
    printf("|^_^|");
    while(cont<ANCHO){ //Imprime una linea con los valores de las celdas
        printf("%2d |", cont);
        cont++;
    }
    putchar('\n');
    cont = 0;
    for(i=0;i<ALTO;i++){
        putchar('|');
        printf("%2d |", cont);//Imprime una fila con los valores de las celdas
        cont++;
        for(j=0;j<ANCHO;j++){
            printf(" %c |", mat[i][j]);//Imprime el caracter de vivo o muerto
        }
        putchar('\n');
    }
}

int numero (void){//Funcion que permite leer numeros que ingrese el usuario
	int num = 0; //Variable que contiene el numero ingresado
    int cont = 0;//Contador para ver si el numero paso por la funcion de pasar a numero
	int c;//Variable que le llega el get chat
	while((c=getchar())!='\n' && c!=','){
		if(c>='0' && c<= '9'){
        	num = (num*10) + (c-'0'); //El ingreso del numero
            cont++; 
       	}
        else if (c=='e' || c=='E'){//Si es q o e iguala num a -1
            num = -1;
            c='\n';
        }
        else if(c=='q' || c=='Q'){//El usuario puede ingresar la letra q para salir del programa, solo cuando se paso a la etapa de "generacion"
            num= 'q';
            c ='\n';
        }
        else{
            printf("Se introdujo un valor invalido\n");
            num = -2;
            c='\n';
        }
    }
    num = num == 0? (cont>0? 0: 1) :num;//Se fija si el valor 0 de num es porque lo ingreso el usuario, si no lo ingreso el usuario es porque presiono enter o coma y pasa una generacion
	return num;
}

void copiar(int mat[ALTO][ANCHO],int matReferencia[ALTO][ANCHO]){ //Funcion que permite copiar matrices
    int j,i;
    for (i = 0; i < ALTO; i++){                                    
        for ( j = 0; j < ANCHO; j++){
            matReferencia[i][j] = mat[i][j];
        }
    }
}

// FUNCIONES CON ALLEGRO 

void must_init(bool test, const char *descripcion)
{
    if(test) return;

    printf("No se pudo inicializar %s\n", descripcion);
    exit(1);
}

void dibujar_filycol(int dispAlto, int dispAncho,float lado){
    int i;
    float offsetx = (dispAncho - lado*ANCHO)/2;
    float offsety = (dispAlto - lado*ALTO)/2; 
    for (i = 0; i <= ANCHO; i++){
        float x = offsetx + i*lado;
        al_draw_line(x,offsety, x, offsety+lado*ALTO, al_map_rgb(255, 0, 255), 0);
    }
    for (i = 0; i <= ALTO; i++){
        float y = offsety + i*lado;
        al_draw_line(offsetx,y, offsetx+lado*ANCHO, y, al_map_rgb(255, 0, 255), 0);
    }
    
    
}

void generacion_allegro( int mat[ALTO][ANCHO], int matReferencia[ALTO][ANCHO]){
    int i, j;//Valor fila columna

        for(i=0;i<ALTO;i++){
            for(j=0;j<ANCHO;j++){
                if (mat[i][j] == ' '){//Se fija si hay una celda muerta
                    nace(mat,matReferencia,i,j);//Manda a revisar si en ese espacio nace una celula
                }
            }
        }
        for(i=0;i<ALTO;i++){
            for(j=0;j<ANCHO;j++){
                if (mat[i][j] == '*'){//Se fija si hay una celda viva
                    muere(mat,matReferencia,i,j);//Manda a revisar si en ese espacio nace una celula
                }
            }
        }
        copiar(mat,matReferencia); //Se copia el lado de la matriz para luego hacer los calculos correspondientes        
}