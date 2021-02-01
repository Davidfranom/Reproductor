#include <stdio.h>
typedef struct Track{
    char title[MAX];
	char performer[MAX];
	char genre[MAX];
	int year;
	float duration;
}Track;
//Poner otra funcion en duracion, por que no muestra el tiempo como debe

Track crear_cancion(){
    Track crear_cancion;
    printf("Ingrese el nombre de la cancion:\n");
    fflush(stdin);
    gets(crear_cancion.title);
    printf("Ingrese el nombre del artista:\n ");
    fflush(stdin);
    gets(crear_cancion.performer);
    printf("Ingrese el genero de la cancion:\n ");
    fflush(stdin);
    gets(crear_cancion.genre);
    printf("Ingrese el año:\n ");
    fflush(stdin);
    scanf("%d",&crear_cancion.year);
    printf("Ingrese la duracion:\n ");
    fflush(stdin);
    scanf("%f",&crear_cancion.duration);
    return crear_cancion;
}
void imprimir_cancion(Track mostrar_cancion){
    printf("Cancion:%s\n",mostrar_cancion.title);
    printf("Artista:%s\n",mostrar_cancion.performer);
    printf("Genero musical:%s\n",mostrar_cancion.genre);
    printf("Año:%d\n",mostrar_cancion.year);
    printf("Duracion:%f\n",mostrar_cancion.duration);
    
}

int main()
{
    Track v1=crear_cancion();
    imprimir_cancion(v1);
}
