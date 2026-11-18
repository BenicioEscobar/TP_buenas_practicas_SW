#include <stdio.h>
#include<stdlib.h>
struct Vuelo {
	char Nombrevuelo[30];
	float FrecuenciaRadio;
	float Distancia;
	
};
void Solicitar_datos(struct Vuelo *p, int N ) {
	int i=0;
	for (i;i<N;i++){
		printf("Datos vuelo nro %i \n",i+1);
		printf("Nombre del vuelo: ");
		scanf("%s", p[i].Nombrevuelo);
		printf("Frecuencia de Radio: \n");
		scanf("%f",&p[i].FrecuenciaRadio);
		printf("Distancia del vuelo: \n");
		scanf("%f",&p[i].FrecuenciaRadio);
	}

}
void ReSolicitar_datos(struct Vuelo *p, int N, int M ) {
	int i=N+1;
	for (i;i<N+M;i++){
		printf("Datos vuelo nro %i",i+1);
		printf("Nombre del vuelo: ");
		scanf("%s", p[i].Nombrevuelo);
		printf("Frecuencia de Radio: ");
		scanf("%f",&p[i].FrecuenciaRadio);
		printf("Distancia del vuelo: ");
		scanf("%f",&p[i].FrecuenciaRadio);
		N++;
	}
}
void Mostrarvuelos (struct Vuelo *c, int N, int M) {
	int i=0;
	for (i;i<M+N;i++) {
		printf("Vuelo %i ", i+1);
		printf("Frecuencia de radio %f", c[i].FrecuenciaRadio);
		printf("Distancia del vuelo %i:  %f ", i+1, c[i].Distancia);
	}
}


void Radio(struct Vuelo *p, int R,int M, int N){
	int bajo;
	int alto;
	int i=0;
	bajo=R-(R/2);
	alto=R+(R/2);
	
	for (i; i<M+N; i++) {
		if (p[i].Distancia<bajo && p[i].Distancia>alto) {
			printf("Frecuencia de vuelo %i %f",i+1, p[i].FrecuenciaRadio);
		} else {
			printf("No hay frecuencias en este radio");
		}
	}
}


	
int main() {

struct Vuelo Bvuelo;
int M;
int N;
int radio;


Bvuelo.FrecuenciaRadio=0;
Bvuelo.Distancia=0;
printf("Coloque la cantidad de vuelos que quiere realizar \n");
scanf("%i",&N);
Solicitar_datos(&Bvuelo,N);
printf("Opciones");
printf("Para agregar otro vuelo presione 1 \n");
printf("Para saber cual es la frecuencia de radio mas cercana presione 2 \n");
printf("Para ver los vuelos subidos presione 3");
scanf("%i",&M);
if (M==1){
		
	printf("Cuantos desea ingresar?");
	scanf("%i",&M);

	ReSolicitar_datos(&Bvuelo,N,M);
	
	
} else if (M==2) {
	printf("Coloque el radio para buscar frecuencias");
	scanf("%i", &radio);
	Radio (&Bvuelo, radio, M, N);

}else if (M==3) {
	Mostrarvuelos(&Bvuelo,N,M);
} 
else ("Respuesta invalida. Intente nuevamente");

	return 0;
}

