#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<pthread.h>

//Variables globales
#define BUFFSIZE 8
int buffer[BUFFSIZE];
int entrada;
int salida;
int contador;
char texto[7];


void *func_prod(void *arg);
void *func_cons(void *arg);
int escribir();
int leer(int item);

// Programa principal
int main(void){

	pthread_attr_t atrib;
	pthread_t hcons, hprod;

	pthread_attr_init(&atrib);
	entrada=0;
	salida=0;
	contador=0;
	pthread_create(&hprod, &atrib, func_prod, NULL);
	pthread_create(&hcons, &atrib, func_cons, NULL);
	pthread_join(hprod, NULL);
	pthread_join(hcons, NULL);

}
//Productor
void *func_prod(void *arg){

	int item;


	while(1){

			printf("Productor funcionando\n");
			item=escribir();
			break;
			

		while (contador == BUFFSIZE){ //bucle estaria vacio y se quedaria en espera
			buffer[entrada]=item;
			entrada= (entrada + 1) % BUFFSIZE;
			contador= contador +1;

		}
	}
}

//Consumidor
void *func_cons(void *arg){

	int item;

	sleep(5);

	while(1){
		while (contador == 0){ //bucle estaria vacio y quedaria en espera
			printf("El consumidor esta funcionando\n");
			item= buffer[salida];
			salida = (salida+1)% BUFFSIZE;
			contador =contador -1;

			leer(item);
        }
			
	   break;
    }
	
}

int escribir() {
	
	printf("Escriba un texto : \n");
	scanf("%s", texto);

	
	return 0;
}


int leer (int item){
	
	printf("El texto que ha escrito es el siguiente: %s \n", texto);
	
	return 0;
}
