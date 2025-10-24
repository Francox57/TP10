#include <stdio.h>
#include "header.h"

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