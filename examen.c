#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10
#define NUM_VOTOS 3

int es_cancion_valida(int cancion);
int leer_votos(int votos[MAX_OYENTES][NUM_VOTOS]);
void inicializar_enteros(int vec[], int tam);
void calcular_puntos_canciones(const int votos[][NUM_VOTOS], int numOyentes, int puntosCanciones[]);
void obtener_top2_canciones(const int puntosCanciones[], int *primera, int *segunda);
int contiene_cancion(const int trio[NUM_VOTOS], int cancion);
int calcular_puntos_oyente(const int trio[NUM_VOTOS], int cancion1, int cancion2);
int obtener_ganador(const int votos[][NUM_VOTOS], int numOyentes, int cancion1, int cancion2, int puntosOyentes[]);
void imprimir_puntos_canciones(const int puntosCanciones[]);
void imprimir_puntos_oyentes(const int puntosOyentes[], int numOyentes);
void imprimir_top2(int primera, int segunda);

int main(void)
{
    int votos[MAX_OYENTES][NUM_VOTOS];
    int puntosCanciones[NUM_CANCIONES];
    int puntosOyentes[MAX_OYENTES];
    int numOyentes;
    int primeraCancion, segundaCancion;
    int ganador;

    printf("Proyecto final - Concurso de radio\n");
    printf("Canciones numeradas del 0 al 9.\n");
    printf("Cada oyente ingresa 3 canciones por orden de preferencia.\n");
    printf("Para terminar, escribe -1 en el primer dato del trio.\n\n");

    numOyentes = leer_votos(votos);

    if (numOyentes == 0)
    {
        printf("\nNo se registraron votos.\n");
        return 0;
    }

    calcular_puntos_canciones(votos, numOyentes, puntosCanciones);
    obtener_top2_canciones(puntosCanciones, &primeraCancion, &segundaCancion);
    ganador = obtener_ganador(votos, numOyentes, primeraCancion, segundaCancion, puntosOyentes);

    printf("\n===== RESULTADOS =====\n");
    imprimir_puntos_canciones(puntosCanciones);
    imprimir_top2(primeraCancion, segundaCancion);
    imprimir_puntos_oyentes(puntosOyentes, numOyentes);

    printf("\nGanador: oyente numero %d con %d puntos\n", ganador, puntosOyentes[ganador]);

    return 0;
}

int es_cancion_valida(int cancion)
{
    return (cancion >= 0 && cancion < NUM_CANCIONES);
}

int leer_votos(int votos[MAX_OYENTES][NUM_VOTOS])
{
    int oyentes = 0;
    int a, b, c;

    while (oyentes < MAX_OYENTES)
    {
        printf("Oyente %d (ingresa 3 canciones, -1 para terminar): ", oyentes);

        if (scanf("%d %d %d", &a, &b, &c) != 3)
        {
            printf("Entrada invalida. El programa termina.\n");
            return oyentes;
        }

        if (a == -1)
        {
            break;
        }

        if (!es_cancion_valida(a) || !es_cancion_valida(b) || !es_cancion_valida(c))
        {
            printf("Error: las canciones deben estar entre 0 y 9, o -1 para terminar.\n");
            continue;
        }

        votos[oyentes][0] = a;
        votos[oyentes][1] = b;
        votos[oyentes][2] = c;

        oyentes++;
    }

    return oyentes;
}

void inicializar_enteros(int vec[], int tam)
{
    for (int i = 0; i < tam; i++)
    {
        vec[i] = 0;
    }
}

void calcular_puntos_canciones(const int votos[][NUM_VOTOS], int numOyentes, int puntosCanciones[])
{
    inicializar_enteros(puntosCanciones, NUM_CANCIONES);

    for (int i = 0; i < numOyentes; i++)
    {
        puntosCanciones[votos[i][0]] += 3;
        puntosCanciones[votos[i][1]] += 2;
        puntosCanciones[votos[i][2]] += 1;
    }
}

void obtener_top2_canciones(const int puntosCanciones[], int *primera, int *segunda)
{
    int idx1 = 0;
    int idx2 = 1;

    if (puntosCanciones[idx2] > puntosCanciones[idx1])
    {
        int temp = idx1;
        idx1 = idx2;
        idx2 = temp;
    }

    for (int i = 2; i < NUM_CANCIONES; i++)
    {
        if (puntosCanciones[i] > puntosCanciones[idx1])
        {
            idx2 = idx1;
            idx1 = i;
        }
        else if (puntosCanciones[i] > puntosCanciones[idx2])
        {
            idx2 = i;
        }
    }

    *primera = idx1;
    *segunda = idx2;
}

int contiene_cancion(const int trio[NUM_VOTOS], int cancion)
{
    for (int i = 0; i < NUM_VOTOS; i++)
    {
        if (trio[i] == cancion)
        {
            return 1;
        }
    }

    return 0;
}

int calcular_puntos_oyente(const int trio[NUM_VOTOS], int cancion1, int cancion2)
{
    int puntos = 0;
    int tiene1 = contiene_cancion(trio, cancion1);
    int tiene2 = contiene_cancion(trio, cancion2);

    if (tiene1)
    {
        puntos += 30;
    }

    if (tiene2)
    {
        puntos += 20;
    }

    if (tiene1 && tiene2)
    {
        puntos += 10;
    }

    return puntos;
}

int obtener_ganador(const int votos[][NUM_VOTOS], int numOyentes, int cancion1, int cancion2, int puntosOyentes[])
{
    int ganador = 0;
    int maxPuntos = -1;

    for (int i = 0; i < numOyentes; i++)
    {
        puntosOyentes[i] = calcular_puntos_oyente(votos[i], cancion1, cancion2);

        if (puntosOyentes[i] > maxPuntos)
        {
            maxPuntos = puntosOyentes[i];
            ganador = i;
        }
    }

    return ganador;
}

void imprimir_puntos_canciones(const int puntosCanciones[])
{
    printf("\nPuntos obtenidos por cada cancion:\n");

    for (int i = 0; i < NUM_CANCIONES; i++)
    {
        printf("Cancion %d: %d puntos\n", i, puntosCanciones[i]);
    }
}

void imprimir_top2(int primera, int segunda)
{
    printf("\n1a cancion mas votada: %d\n", primera);
    printf("2a cancion mas votada: %d\n", segunda);
}

void imprimir_puntos_oyentes(const int puntosOyentes[], int numOyentes)
{
    printf("\nPuntos por oyente:\n");

    for (int i = 0; i < numOyentes; i++)
    {
        printf("Oyente %d: %d puntos\n", i, puntosOyentes[i]);
    }
}
