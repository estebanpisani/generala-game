#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Valores de puntajes de cada categoría
#define ESCALERA_VALUE 35
#define FULL_VALUE 50
#define POKER_VALUE 75
#define GENERALA_VALUE 100
#define GENERALA_DOBLE_VALUE 120
#define LANZAMIENTOS_MAX 3
#define TURNOS_MAX 11
#define DADOS_MAX 5

//Funciones útiles
int arrojarDado(){
    int dadoRandom = rand() % (7);
    return dadoRandom;
}

void mostrarDado(int dadoId, int dado){
    printf("- Dado %d: %d \n", dadoId, dado);
}

void separador(){
    printf("-------------------\n");
}

int main(){
    int categorias[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int cantidadJugadores = 0;
    int turno = 1;
    int lanzamientosRestantes = LANZAMIENTOS_MAX;
    int cantidadARelanzar = 0;
    int dadosActuales[DADOS_MAX];
    char jugador1[21] = "";
    char jugador2[21] = "";

    printf("¡Hola!, bienvenido al juego de la Generala!\n");
    do{
        printf("Elija la cantidad de jugadores (1 o 2):\n");
        scanf("%d", &cantidadJugadores);
        if(cantidadJugadores != 1 && cantidadJugadores != 2){
            printf("¡Solo pueden jugar 1 o 2 jugadores!\n");
            printf("Inténtelo de nuevo.\n");
        }
    } while(cantidadJugadores != 1 && cantidadJugadores != 2);

    for(int i=1; i<=cantidadJugadores; i++){
        printf("Ingrese el nombre del jugador %d:\n", i);
        if(i==1){
            scanf("%s",jugador1);
            printf("Bienvenido %s!\n", jugador1);
        } else{
            scanf("%s",jugador2);
            printf("Bienvenido %s!\n", jugador2);           
        }
    }

    //TODO lógica turnos (for doble)
    //LOOP
    //Si turno==1
    printf("A continuación %s tirará los 5 dados por primera vez.\n", jugador1);
    printf("Arrojando dados...\n");
    for (int i = 0; i < DADOS_MAX; i++)
    {
        dadosActuales[i] = arrojarDado();
        mostrarDado(i+1, dadosActuales[i]);
    }
    lanzamientosRestantes--;
    printf("Lanzamientos restantes: %d \n", lanzamientosRestantes);
    do{
       printf("Cuántos dados desea relanzar? (0 = ninguno)\n");
       scanf("%d", &cantidadARelanzar);

        if(cantidadARelanzar<0 || cantidadARelanzar>5){
            printf("Ingrese una cantidad correcta!! (0 a 5)\n");
            continue;
        }

        if(cantidadARelanzar != 0){
        if(cantidadARelanzar ==5){
            printf("Relanzando todos los dados...\n");
            for (int i = 0; i < DADOS_MAX; i++){
                dadosActuales[i] = arrojarDado();
            }   
        } else {
            separador();
            printf("SELECCIONAR DADOS\n");
            separador();
            //Seleccionar dados
            int dadosReemplazos[cantidadARelanzar];
            for(int i=0; i<cantidadARelanzar; i++){
                printf("Ingrese el número de dado que quiere relanzar (%d/%d) \n", i+1, cantidadARelanzar);
                scanf("%d", &dadosReemplazos[i]);
            }
            //Reemplazar dados seleccionados
            printf("Relanzando dados...\n");
            for (int i = 0; i < (sizeof(dadosReemplazos)/ sizeof(dadosReemplazos[0])); i++)
            {
                dadosActuales[dadosReemplazos[i]-1] = arrojarDado();
            }
        }
        separador();
        //Mostrar dados actualizados
        for (int i = 0; i < DADOS_MAX; i++)
        {
            mostrarDado(i+1, dadosActuales[i]);
        }
        //Lanzamientos restantes:
        lanzamientosRestantes--;
        if(lanzamientosRestantes == 0){
            printf("Ya no le quedan lanzamientos en este turno.\n");
        } else {
            printf("Lanzamientos restantes: %d \n", lanzamientosRestantes);
        }
       }
    } while(lanzamientosRestantes>0 && cantidadARelanzar!=0);

    printf("Fin.\n");
   
    //while turno<=11
    //Turno 1: 
    //
        //while (lanzamiento i=1; i++, i<=3)
        //Mostrar resultados según indice = dado
        //¿Cuántos dados desea arrojar? x 2
        //  - 0 (Pasar y anotar categoría) (break)
        //  - 1-5 (cantidadDados) (for)
        //
        // Ingresar Índice de dados (1 a 5) (guardar en array dadosSelect)
        // Repeat while
    //Evaluando categorías...
    //Evaluar categorías posibles
    //switch
    //

    



    return 0;
}