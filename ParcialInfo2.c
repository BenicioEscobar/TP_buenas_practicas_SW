#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 30
void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

struct Vuelo {
    char Nombrevuelo[MAX_NOMBRE];
    float FrecuenciaRadio;
    float Distancia;
};

void Solicitar_datos(struct Vuelo *p, int inicio, int cantidad) {
    for (int i = inicio; i < cantidad; i++) {
        printf("\nDatos vuelo nro %d\n", i + 1);
        printf("Nombre del vuelo: ");
        scanf("%29s", p[i].Nombrevuelo);
        printf("Frecuencia de Radio (MHz): ");
        scanf("%f", &p[i].FrecuenciaRadio);
        printf("Distancia del vuelo (km): ");
        scanf("%f", &p[i].Distancia);
    }
}

void Mostrarvuelos(struct Vuelo *vuelos, int total) {
    for (int i = 0; i < total; i++) {
        printf("\nVuelo %d: %s | Frecuencia: %.2f MHz | Distancia: %.2f km\n",
               i + 1, vuelos[i].Nombrevuelo, vuelos[i].FrecuenciaRadio, vuelos[i].Distancia);
    }
}

void BuscarPorFrecuencia(struct Vuelo *p, float frecBuscada, float porcentaje, int total) {
    float margen = frecBuscada * (porcentaje / 100.0f);
    float minimo = frecBuscada - margen;
    float maximo = frecBuscada + margen;
    int encontrados = 0;

    printf("\nBuscando vuelos entre %.2f MHz y %.2f MHz:\n", minimo, maximo);
    for (int i = 0; i < total; i++) {
        if (p[i].FrecuenciaRadio >= minimo && p[i].FrecuenciaRadio <= maximo) {
            printf("- Vuelo %d: %s | Frecuencia: %.2f MHz | Distancia: %.2f km\n",
                   i + 1, p[i].Nombrevuelo, p[i].FrecuenciaRadio, p[i].Distancia);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("No se encontraron vuelos dentro de ese porcentaje.\n");
    }
}

int main() {
    struct Vuelo *Bvuelo = NULL;
    int totalVuelos = 0;
    int nuevos = 0;
    int opcion = 0;
    float radio = 0;

    printf("Coloque la cantidad de vuelos iniciales: ");
    scanf("%d", &totalVuelos);

    if (totalVuelos > 0) {
        Bvuelo = (struct Vuelo *) malloc(totalVuelos * sizeof(struct Vuelo));
        if (Bvuelo == NULL) {
            printf("Error al asignar memoria.\n");
            return 1;
        }
        Solicitar_datos(Bvuelo, 0, totalVuelos);
    }

    do {
        printf("\n--- Opciones ---\n");
        printf("1. Agregar otro/s vuelo/s\n");
        printf("2. Buscar vuelos por radio\n");
        printf("3. Ver los vuelos subidos\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        if (opcion == 1) {
            printf("Cuantos vuelos desea ingresar?: ");
            scanf("%d", &nuevos);
            if (nuevos > 0) {
                struct Vuelo *temp = (struct Vuelo *) realloc(Bvuelo, (totalVuelos + nuevos) * sizeof(struct Vuelo));
                if (temp == NULL) {
                    printf("Error al redimensionar memoria.\n");
                    free(Bvuelo);
                    return 1;
                }
                Bvuelo = temp;
                Solicitar_datos(Bvuelo, totalVuelos, totalVuelos + nuevos);
                totalVuelos += nuevos;
            }
        } } else if (opcion == 2) {
            float frecBuscada = 0, porcentaje = 0;
            printf("Ingrese la frecuencia de radio a buscar (MHz): ");
            scanf("%f", &frecBuscada);
            printf("Ingrese el porcentaje de tolerancia (ej. 10 para 10%%): ");
            scanf("%f", &porcentaje);
            BuscarPorFrecuencia(Bvuelo, frecBuscada, porcentaje, totalVuelos);
        } else if (opcion == 3) {
            Mostrarvuelos(Bvuelo, totalVuelos);
        } else if (opcion != 4) {
            printf("Respuesta invalida. Intente nuevamente.\n");
        }
    } while (opcion != 4);

    free(Bvuelo);
    return 0;
}