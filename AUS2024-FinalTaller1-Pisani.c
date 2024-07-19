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

void ordenarDados(int dados[]){
    int aux = 0;
    for (int i = 0; i < DADOS_MAX-1; i++){
        for (int j = 0; j < DADOS_MAX-1; j++)
        {
            if (dados[j]>dados[j+1])
            {
                aux = dados[j+1];
                dados[j+1] = dados[j];
                dados[j] = aux;
            }
        }
        
    }
}

int contarNumero(int dados[], int numero){
    int cantidad = 0;
    for (int i = 0; i < DADOS_MAX; i++)
    {
        if(dados[i] == numero){
            cantidad++;
        }
    }
    return cantidad;
}

//TODO Full
int tieneFull(int dados[]){
    int cantidad = 0;
    int condiciones = 0;
    for (int i = 0; i < DADOS_MAX; i++)
    {
        cantidad = contarNumero(dados, i);
        if(cantidad == 2){
            condiciones++;
        }
        if(cantidad == 3){
            condiciones++;
        }
        cantidad = 0;
    }
    return condiciones == 2;
}

int tienePoker(int dados[]){
    int cuenta = 0;

    for (int j = 0; j <= 1; j++)
    {
        for (int i = 0; i < DADOS_MAX; i++)
        {
            if(j==i){
                continue;
            }
            if(dados[j] == dados[i]){
                cuenta++;
            }
            if(cuenta == 3){
                break;
            }
        }
        if(cuenta == 3){
            break;
        } else {
            cuenta = 0;
        }
    }
    return cuenta == 3;
}

int tieneGenerala(int dados[]){
    int cuenta = 0;
    for (int i = 0; i < DADOS_MAX-1; i++)
    {
        if(dados[i] == dados[i+1]){
            cuenta++;
            continue;
        } else {
            break;
        }
    }
    return cuenta == 4;
}

int tieneEscalera(int dados[]){
    ordenarDados(dados);
    int escalera = 0;
    for (int i = 0; i < DADOS_MAX-1; i++)
    {
        if(dados[i] == dados[i+1]-1){
            escalera++;
            continue;
        } else {
            break;
        }
    }
    return escalera == 4;
}

/*
    1) Anotarse: 0 al 1
    2) Anotarse: 0 al 2
    3) Anotarse: 6 al 3
    4) Anotarse: 12 al 4
    5) Anotarse: 0 al 6
    6) Tacharse: Escalera
    7) Anotarse: Full
    8) Tacharse: Poker
    9) Tacharse: Doble Generala
*/



void mostrarCategorias(int dados[], int categorias[]){
    int cuenta = 1;

    for (int i = 0; i < 6; i++)
    {
        if(!categorias[i]){
            printf("%d) Anotarse: ", cuenta);
            printf("%d al ", (i+1 * contarNumero(dados, i+1)));
            printf("%d \n", i+1);
            cuenta++;
        }
    }

    for (int i = 6; i < 11; i++)
    {
        if (!categorias[i]){
            printf("%d) ", cuenta);
            switch (i) {
                case 6:
                    if(tieneEscalera(dados)){
                        printf("Anotarse ");
                    } else {
                        printf("Tacharse ");
                    }
                    printf("Escalera.\n");
                break;
                case 7:
                    if (tieneFull(dados)) {
                        printf("Anotarse ");
                    } else {
                        printf("Tacharse ");
                    }
                    printf("Full.\n");
                break;
                case 8:
                    if (tienePoker(dados)) {
                        printf("Anotarse ");
                    } else {
                        printf("Tacharse ");
                    }
                    printf("Póker.\n");
                break;
                case 9:
                    if (tieneGenerala(dados)) {
                        printf("Anotarse ");
                    } else {
                        printf("Tacharse ");
                    }
                    printf("Generala.\n");
                break;
                case 10:
                    if(tieneGenerala(dados)){
                        printf("Anotarse ");
                    } else {
                        printf("Tacharse ");
                    }
                    printf("Generala Doble.\n");
                break;                
                default:
                    break;
            }
                       
            cuenta++;
        }

    }
    
}


int main(){
    int cantidadJugadores = 0;
    int turnoJugador1 = 1;
    int turnoJugador2 = 1;
    int lanzamientosRestantes = LANZAMIENTOS_MAX;
    int cantidadARelanzar = 0;
    int dadosActuales[DADOS_MAX];
    char jugador1[21] = "";
    char jugador2[21] = "";
    int opcion = 0;
    // CATEGORÍAS (índices)
    // 0 - 5 = 1 - 6
    // 6 = Escalera
    // 7 = Full
    // 8 = Póker
    // 9 = Generala
    // 10 = Generala Doble
    // ESTADOS (valor)
    // 0 - Disponible
    // 1 - Usado
    int categorias[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


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

    //TODO lógica Jugador1s (for doble)
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

        if(cantidadARelanzar<0 || cantidadARelanzar>DADOS_MAX){
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

    separador();
    printf("Si esto andara, podrías hacer todo esto:\n");
    mostrarCategorias(dadosActuales);
    printf("Pero todavía no se puede hacer nada.\n");
    printf("Fin.\n");
   
    return 0;
}