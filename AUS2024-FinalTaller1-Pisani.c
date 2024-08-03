#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Valores de puntajes de cada categoría
#define ESCALERA_VALUE 35
#define FULL_VALUE 50
#define POKER_VALUE 75
#define GENERALA_VALUE 100
#define GENERALA_DOBLE_VALUE 120
#define LANZAMIENTOS_MAX 3
#define TURNOS_MAX 11
#define TURNOS_MAX_DOBLE 22
#define DADOS_MAX 5
#define USADO_VALUE 1
#define LIBRE_VALUE 0
#define SEPARADOR printf("-------------------\n");

// Funciones útiles

void imprimirCategoria(int index)
{
    switch (index)
    {
    case 0 ... 5:
        printf("%d", index);
        break;
    case 6:
        printf("ESCALERA");
        break;
    case 7:
        printf("FULL");
        break;
    case 8:
        printf("PÓKER");
        break;
    case 9:
        printf("GENERALA");
        break;
    case 10:
        printf("GENERALA DOBLE");
        break;
    default:
        break;
    }
}

void anotarCategoria(int categoria, int tablaPuntajes[], int puntaje)
{
    printf("Anotando %d puntos.\n", puntaje);
    tablaPuntajes[categoria] = puntaje;
}

int arrojarDado()
{
    int dadoRandom = (rand() % (6 - 1 + 1)) + 1;
    return dadoRandom;
}

//SOLO PARA TESTEAR GENERALA DOBLE
int sacarGenerala()
{
    int dadoRandom = 6;
    return dadoRandom;
}

void mostrarDado(int dadoId, int dado)
{
    printf("- Dado %d: %d \n", dadoId, dado);
}

void ordenarDados(int dados[])
{
    int aux = 0;
    for (int i = 0; i < DADOS_MAX - 1; i++)
    {
        for (int j = 0; j < DADOS_MAX - 1; j++)
        {
            if (dados[j] > dados[j + 1])
            {
                aux = dados[j + 1];
                dados[j + 1] = dados[j];
                dados[j] = aux;
            }
        }
    }
}

int contarNumero(int dados[], int numero)
{
    int cantidad = 0;
    for (int i = 0; i < DADOS_MAX; i++)
    {
        if (dados[i] == numero)
        {
            cantidad++;
        }
    }
    return cantidad;
}

int tieneFull(int dados[])
{
    int cantidad = 0;
    int condicionDos = 0;
    int condicionTres = 0;
    for (int i = 1; i <=6; i++)
    {
        cantidad = contarNumero(dados, i);
        if (cantidad == 2)
        {
            condicionDos = 1;
        }
        if (cantidad == 3)
        {
            condicionTres = 1;
        }
    }
    return condicionDos && condicionTres;
}

int tienePoker(int dados[])
{
    int cantidad = 0;
    for (int i = 1; i <=6; i++)
    {
        cantidad = contarNumero(dados, i);
        if (cantidad == 4)
        {
            return 1;
        }
    }
    return 0;
}

int tieneGenerala(int dados[])
{
    int cuenta = 0;
    for (int i = 0; i < DADOS_MAX - 1; i++)
    {
        if (dados[i] == dados[i + 1])
        {
            cuenta++;
            continue;
        }
        else
        {
            break;
        }
    }
    return cuenta == 4;
}

int tieneEscalera(int dados[])
{
    ordenarDados(dados);
    int escalera = 0;
    for (int i = 0; i < DADOS_MAX - 1; i++)
    {
        if (dados[i] == dados[i + 1] - 1)
        {
            escalera++;
            continue;
        }
        else
        {
            break;
        }
    }
    return escalera == 4;
}

void mostrarCategorias(int dados[], int categoriasUsadas[], int *generalaDoble)
{
    // TODO revisar y testear Generala Doble
    int cuenta = 1;

    for (int i = 0; i < 6; i++)
    {
        if (!categoriasUsadas[i])
        {
            printf("%d) Anotarse: ", cuenta);
            printf("%d al ", (contarNumero(dados, i + 1) * (i + 1)));
            printf("%d \n", i + 1);
            cuenta++;
        }
    }

    for (int i = 6; i < 11; i++)
    {
        if (!categoriasUsadas[i])
        {
            printf("%d) ", cuenta);
            switch (i)
            {
            case 6:
                if (tieneEscalera(dados))
                {
                    printf("Anotarse ");
                }
                else
                {
                    printf("Tacharse ");
                }
                break;
            case 7:
                if (tieneFull(dados))
                {
                    printf("Anotarse ");
                }
                else
                {
                    printf("Tacharse ");
                }
                break;
            case 8:
                if (tienePoker(dados))
                {
                    printf("Anotarse ");
                }
                else
                {
                    printf("Tacharse ");
                }
                break;
            case 9:
                if (tieneGenerala(dados))
                {
                    printf("Anotarse ");
                }
                else
                {
                    printf("Tacharse ");
                }
                break;
            case 10:
                if (tieneGenerala(dados) && *generalaDoble)
                {
                    printf("Anotarse ");
                }
                else
                {
                    printf("Tacharse ");
                }
                break;
            default:
                break;
            }
            imprimirCategoria(i);
            printf(".\n");
            cuenta++;
        }
    }
}

void procesarCategorias(int dados[], int categoriasUsadas[], int tablaPuntajes[], int *generalaDoble, int opcion)
{
    int puntaje = 0;
    int cuenta = 0;
    for (int i = 0; i < 11; i++)
    {
        if (!categoriasUsadas[i])
        {
            cuenta++;
            if (cuenta == opcion)
            {
                switch (i)
                {
                case 0 ... 5:
                    puntaje = (contarNumero(dados, i + 1) * (i + 1));
                    break;
                case 6:
                    if (tieneEscalera(dados))
                    {
                        puntaje = ESCALERA_VALUE;
                    }
                    break;
                case 7:
                    if (tieneFull(dados))
                    {
                        puntaje = FULL_VALUE;
                    }
                    break;
                case 8:
                    if (tienePoker(dados))
                    {
                        puntaje = POKER_VALUE;
                    }
                    break;
                case 9:
                    if (tieneGenerala(dados))
                    {
                        puntaje = GENERALA_VALUE;
                        *generalaDoble = 1;
                    } else {
                        *generalaDoble = 0;
                    }
                    break;
                case 10:
                    if (tieneGenerala(dados) && *generalaDoble)
                    {
                        puntaje = GENERALA_DOBLE_VALUE;
                        *generalaDoble = 0;
                    }
                    break;
                default:
                    break;
                }
                anotarCategoria(i, tablaPuntajes, puntaje);
                categoriasUsadas[i] = USADO_VALUE;
            }
        }
    }
    
}

int validarOpcion(int categoriasUsadas[], int opcion){
    int cuenta = 0;
    int coincidencia = 0;
    for (int i = 0; i < 11; i++)
    {
        if (!categoriasUsadas[i])
        {
            cuenta++;
            if (cuenta == opcion){
                coincidencia = 1;
                return coincidencia;
            }
        }
    }
    return coincidencia;
}

int contarPuntos(int categorias[])
{
    int puntuacion = 0;

    for (int i = 0; i < TURNOS_MAX; i++)
    {
        puntuacion += categorias[i];
    }
    return puntuacion;
}

int main()
{
    int cantidadJugadores = 1;
    int turnoJugador1 = 1;
    int lanzamientosRestantes = LANZAMIENTOS_MAX;
    int cantidadARelanzar = 0;
    //int dadosActuales[DADOS_MAX];
    //DADOS TEST
    int dadosActuales[DADOS_MAX] = {6,6,6,6,6};
    char jugador1[21] = "";
    char jugador2[21] = "";
    int opcion = 0;
    // VALORES generalaDoble
    // 0 - No puede hacer generala doble.
    // 1 - Puede hacer generala Doble.
    int generalaDobleJugador1 = LIBRE_VALUE;
    int generalaDobleJugador2 = LIBRE_VALUE;
    int turnosPasadosJugador1 = 0;
    int turnosPasadosJugador2 = 0;

    // CATEGORÍAS (índices)
    //
    // 0 - 5 = 1 - 6
    // 6 = Escalera
    // 7 = Full
    // 8 = Póker
    // 9 = Generala
    // 10 = Generala Doble
    int tablaPuntajesJugador1[TURNOS_MAX] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int tablaPuntajesJugador2[TURNOS_MAX] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // ESTADOS (categoriasUsadas)
    // 0 - Disponible
    // 1 - Usado
    int categoriasUsadasJugador1[TURNOS_MAX] = {LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE};
    int categoriasUsadasJugador2[TURNOS_MAX] = {LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE, LIBRE_VALUE};
    int puntuacionJugador1 = 0;
    int puntuacionJugador2 = 0;
    int opcionValida = 0;
    srand(time(0));

    printf("¡Hola!, ¡bienvenido al juego de la Generala!\n");
    do
    {
        printf("Elija la cantidad de jugadores (1 o 2):\n");
        scanf("%d", &cantidadJugadores);
        if (cantidadJugadores != 1 && cantidadJugadores != 2)
        {
            printf("¡Solo pueden jugar 1 o 2 jugadores!\n");
            printf("Inténtelo de nuevo.\n");
        }
    } while (cantidadJugadores != 1 && cantidadJugadores != 2);

    //REGISTRO
    for (int i = 1; i <= cantidadJugadores; i++)
    {
        printf("Ingrese el nombre del jugador %d:\n", i);
        if (i == 1)
        {
            scanf("%s", jugador1);
            printf("¡Bienvenido %s!\n", jugador1);
            printf("\n");
        }
        else
        {
            scanf("%s", jugador2);
            printf("¡Bienvenido %s!\n", jugador2);
            printf("\n");
        }
    }

    // Inicio juego
    for (int i = 1; i <= (cantidadJugadores == 1 ? TURNOS_MAX : TURNOS_MAX_DOBLE); i++)
    {
        lanzamientosRestantes = LANZAMIENTOS_MAX;
        if (turnoJugador1)
        {
            turnosPasadosJugador1++;
        }
        else
        {
            turnosPasadosJugador2++;
        }
        SEPARADOR
        printf("Juega %s:\n", turnoJugador1 ? jugador1 : jugador2);
        printf("Turno %d/%d.\n", turnoJugador1 ? turnosPasadosJugador1 : turnosPasadosJugador2, TURNOS_MAX);

        printf("Arrojando dados...\n");
        for (int i = 0; i < DADOS_MAX; i++)
        {
            dadosActuales[i] = arrojarDado();
            mostrarDado(i + 1, dadosActuales[i]);
        }
        lanzamientosRestantes--;
        // OPCIONES
        do
        {
            printf("Cuántos dados desea relanzar? (0 = ninguno)\n");
            scanf("%d", &cantidadARelanzar);

            if (cantidadARelanzar < 0 || cantidadARelanzar > DADOS_MAX)
            {
                printf("Ingrese una cantidad correcta!! (0 a %d)\n", DADOS_MAX);
                continue;
            }

            if (cantidadARelanzar != 0)
            {
                if (cantidadARelanzar == DADOS_MAX)
                {
                    printf("Relanzando todos los dados...\n");
                    for (int i = 0; i < DADOS_MAX; i++)
                    {
                        dadosActuales[i] = arrojarDado();
                    }
                }
                else
                {
                    SEPARADOR
                    printf("SELECCIONAR DADOS\n");
                    SEPARADOR
                    // Seleccionar dados
                    int dadosReemplazos[cantidadARelanzar];
                    for (int i = 0; i < cantidadARelanzar; i++)
                    {
                        printf("Ingrese el número de dado que quiere relanzar (%d/%d) \n", i + 1, cantidadARelanzar);
                        scanf("%d", &dadosReemplazos[i]);
                        if (dadosReemplazos[i] < 0 || dadosReemplazos[i] > DADOS_MAX)
                        {
                            printf("Ingrese una cantidad correcta!! (1 a %d)\n", DADOS_MAX);
                            i--;
                            continue;
                        }
                    }
                    // Reemplazar dados seleccionados
                    printf("Relanzando dados...\n");
                    for (int i = 0; i < (sizeof(dadosReemplazos) / sizeof(dadosReemplazos[0])); i++)
                    {
                        dadosActuales[dadosReemplazos[i] - 1] = arrojarDado();
                    }
                }
                SEPARADOR
                // Mostrar dados actualizados
                for (int i = 0; i < DADOS_MAX; i++)
                {
                    mostrarDado(i + 1, dadosActuales[i]);
                }
                // Mostrar lanzamientos restantes
                lanzamientosRestantes--;
                if (lanzamientosRestantes == 0)
                {
                    printf("Ya no le quedan lanzamientos en este turno.\n");
                }
                else
                {
                    printf("Lanzamientos restantes: %d \n", lanzamientosRestantes);
                }
            }
        } while (lanzamientosRestantes > 0 && cantidadARelanzar != 0);

        SEPARADOR
        if (turnoJugador1)
        {
            mostrarCategorias(dadosActuales, categoriasUsadasJugador1, &generalaDobleJugador1);
        }
        else
        {
            mostrarCategorias(dadosActuales, categoriasUsadasJugador2, &generalaDobleJugador2);
        }

        do{
            printf("\n¿Qué desea hacer?:\n");
            scanf("%d", &opcion);
            
            if (turnoJugador1)
            {
                opcionValida = validarOpcion(categoriasUsadasJugador1, opcion);
            } else {
                opcionValida = validarOpcion(categoriasUsadasJugador2, opcion);
            }
            
            if(!opcionValida){
                printf("Ingrese una opción correcta!\n");
            }
        }while (!opcionValida);
        
        if (turnoJugador1)
        {
            procesarCategorias(dadosActuales, categoriasUsadasJugador1, tablaPuntajesJugador1, &generalaDobleJugador1, opcion);
        }
        else
        {
            procesarCategorias(dadosActuales, categoriasUsadasJugador2, tablaPuntajesJugador2, &generalaDobleJugador2, opcion);
        }

        // Cambio de turno
        if (cantidadJugadores > 1)
        {
            turnoJugador1 = turnoJugador1 ? 0 : 1;
        }
    }

    //RESULTADOS
    puntuacionJugador1 = contarPuntos(tablaPuntajesJugador1);
    SEPARADOR
    printf("RESULTADOS:\n");
    SEPARADOR
    printf("Jugador: %s\n", jugador1);
    SEPARADOR
    for (int i = 0; i < TURNOS_MAX; i++)
    {
        printf("Categoria ");
        imprimirCategoria(i);
        printf(" tiene %d puntos.\n", tablaPuntajesJugador1[i]);
    }
    printf("Puntuación total de %s: %d.\n", jugador1, puntuacionJugador1);
    if (cantidadJugadores == 2)
    {
        puntuacionJugador2 = contarPuntos(tablaPuntajesJugador2);
        SEPARADOR
        printf("Jugador: %s\n", jugador2);
        SEPARADOR
        for (int i = 0; i < TURNOS_MAX; i++)
        {
            printf("Categoria %d tiene %d puntos.\n", i, tablaPuntajesJugador2[i]);
        }
        printf("Puntuación total de %s: %d.\n", jugador2, puntuacionJugador2);
        SEPARADOR
        printf("RESULTADO FINAL:\n");
        if (puntuacionJugador1 > puntuacionJugador2)
        {
            printf("El GANADOR es: %s. ¡Felicitaciones!\n", jugador1);
        }
        else if (puntuacionJugador1 < puntuacionJugador2)
        {
            printf("El GANADOR es: %s. ¡Felicitaciones!\n", jugador2);
        }
        else
        {
            printf("\n El resultado de la partida es EMPATE.\n");
        }
    }
    
    return 0;
}