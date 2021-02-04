# Reproductor
Reproductor de música
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUSCAR 50
#define CANCION 50
#define NUM_BYTES 160

// en este caso la segunda palabra seria la canción

void leer (char *p1, char * p2){

  printf ("\nIngrese el nombre de la cancion a buscar es : ");
  fgets (p1,BUSCAR , stdin);
  p1[strlen (p1) - 1] = '\0';	//strlen sirve para contar el número de letras que tiene una cadena de caracteres

  printf ("\nLa cancion: ");
  fgets (p2,CANCION, stdin);
  p2[strlen(p2) - 1]='\0' ;
  printf ("\n");
}

void mostrar (char *p1, char* p2){

  printf ("\nLa cancion a buscar es %s y la cancion es %s\n\n", p1,p2);
}
void comparar(char * p1, char * p2){

	int resultado = strcmp(p1, p2);
	if (NULL == resultado)
		printf("\n Si se encontro la canción \n");
	else {
		printf("\n No se encontro la canción  \n");
	}
	
}
void buscar(char * p1, char * p2, char * pc)
{
	char * resultado = NULL;
	printf("\nEscriba la palabra que busca: ");
	fgets(pc, NUM_BYTES, stdin);
	pc[strlen(pc)-1] = '\0';
	resultado =  strstr(p1, pc);
	if (NULL == resultado)
		printf("\n%s no contiene a %s\n",p1,pc);
	else {
		printf("\n%s contiene a %s\n",p1,pc);
	}
	
}
	
	
	



int main(){
    
	char palabra_1[BUSCAR]; 
	char palabra_2[CANCION];
	
	char * cadena = malloc((BUSCAR+CANCION)*sizeof(char));
	
	char menu[] = "1)Leer 2)Mostrar 3)Comparar 4)Buscar Q) Salir";
	
	char opcion;

	int index = 0;
	do {
		printf("%s ", menu);
		scanf("%c%*c",&opcion);
		switch (opcion) {
			case '1':
				printf("\nIngresa la canción\n");
				leer(palabra_1, palabra_2);
				break;
			case '2':
				printf("\nMuestra la cancion ingresada\n");
				mostrar(palabra_1, palabra_2);
				break;
			case '3':
			    printf("\nCompara la cancion a buscar con la que ya estaba en la lista\n");
				comparar(palabra_1, palabra_2);
				break;
			case '4':
			    printf("\nBusca una palabra similar que se encuentre en alguna de las canciones\n");
				buscar(palabra_1, palabra_2,cadena);
				break;	
			case 'Q':
				printf("\nTermino programa\n");
				index = 1;
				break;
			default:
				break;
		}
	} while (!index);
    return 0;
}
