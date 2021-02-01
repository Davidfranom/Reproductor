#include <stdlib.h>
#include <stdio.h>
//Track->pista
typedef struct Track{
	char* title;
	char* performer;
	char* genre;
	int year;
	float duration;
}Track;

int Leer_Cadena(char ** cadena);
void capturar(Track*cancion);
void mostrar_todo(Track*cancion);
int Leer_Cadena(char ** cadena){
    char c;
    int i;
    
    if((*cadena)!=NULL){
        free(*cadena);
        (*cadena)=NULL;
        i=1;
    
        fflush(stdin);
        while((c=getchar())!='\n'){
            (*cadena)=(char*)realloc((*cadena),(i+2)*sizeof(char));
            if((*cadena)==NULL){
                printf("Insuficiente espacio de memoria");exit(1);
            }
            (*cadena)[i-1]=c;
            (*cadena)[i]='\0';
            i++;
            
        }
        if((*cadena)==NULL){
            return 0;
        }
        return 1;
    }
}

void capturar(Track*cancion){
    cancion=NULL;
    int n=0;
    printf("Cuantas canciones registrara:");
    scanf("%d",&n);
    cancion=(Track*)malloc(n*sizeof(Track));
    if(cancion!=NULL){
        for(int i=0;i<n;i++){
        printf("Introduzca el nombre de la canción:");
        Leer_Cadena(&cancion->title[i]);
        printf("Introduzca el nombre del artista:");
        Leer_Cadena(&cancion->performer[i]);
        printf("Introduzca el genero de la canción:");
        Leer_Cadena(&cancion->genre[i]);
        
        }
        
    }
    printf("Introduzca el año de la canción:");
    scanf("%d",&cancion->year);
    printf("Introduzca la duración:");
    scanf("%f",&cancion->duration);
       
    
void mostrar_todo(Track*cancion){
    for(int i=0;i<n;i++){
        printf("La canción es:%s",cancion->title[i]);
        printf("El artista es:%s",cancion->performer[i]);
        printf("El artista es:%s",cancion->genre[i]);
       }
    
    printf("El año es:%d",cancion->year);
    printf("La duracion  es:%f",cancion->duration);
    
}     
   
 

int main(){
    Track cancion;
    capturar(&cancion);
    Leer_Cadena(cancion);
    mostrar_todo(&cancion);
    
}
