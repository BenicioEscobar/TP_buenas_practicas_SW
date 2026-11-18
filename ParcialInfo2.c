#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 30

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

void Radio(struct Vuelo *p, float R, int total) {
    float bajo = R - (R / 2.0f);
    float alto = R + (R / 2.0f);
    int encontrados = 0;

    for (int i = 0; i < total; i++) {
        if (p[i].Distancia >= bajo && p[i].Distancia <= alto) {
            printf("Vuelo %d (%s) - Frecuencia: %.2f MHz - Distancia: %.2f km\n",
                   i + 1, p[i].Nombrevuelo, p[i].FrecuenciaRadio, p[i].Distancia);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("No hay vuelos en este rango.\n");
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
        } else if (opcion == 2) {
            printf("Coloque el radio para buscar frecuencias: ");
            scanf("%f", &radio);
            Radio(Bvuelo, radio, totalVuelos);
        } else if (opcion == 3) {
            Mostrarvuelos(Bvuelo, totalVuelos);
        } else if (opcion != 4) {
            printf("Respuesta invalida. Intente nuevamente.\n");
        }
    } while (opcion != 4);

    free(Bvuelo);
    return 0;
}