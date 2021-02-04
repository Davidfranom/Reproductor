#define MAX 50
#include <stdio.h>
#include <string.h>
typedef struct Track{
    char title[MAX];
	char performer[MAX];
	char genre[MAX];
	int year;
	int  duration;
	int lleno_canciones;
}Track;

typedef struct PlayList{
    char nombre_PlayList[MAX];//Nombre de la lista de canciones 
    Track canciones [10];//canciones que se pueden agregar 
    int lleno_Playlist;
}PlayList;

PlayList C_PlayList [3];//canciones que hay en la playlist 
void vacio();
void cambio(char palabra[MAX]);
void add_PlayList();
void add_Track();
main(){
    int op;
	char key;
	
	vacio();
	
	do{
		do{
			printf("Elige una opcion a realizar: \n");
			printf("(1) Añadir una nueva PlayList.\n");
			printf("(2) Añadir un cancion a una PlayList.\n");
			printf("(3) Consultar Playlist.\n");
			scanf("%i",&op);
			
		}while(op < 1 || op > 3);
		
		switch(op){
			case 1:{
			   add_PlayList();
				break;
			}
			case 2:{
				add_Track();
				break;
			}
			case 3:{
				//consulta();
				break;
			}
		}
		printf("Quieres realizar alguna operacion mas? (S/N): ");
		fflush(stdin);
		scanf("%c",&key);
	}while(key == 'S' || key == 's');
    
}

void vacio(){
    for (int i = 0; i < 3; i++){
		C_PlayList [i].lleno_Playlist = 0;
		for (int j = 0; j < 10; j++){
			C_PlayList[i].canciones[j].lleno_canciones = 0;
		}
	}
}

void cambio(char palabra[MAX]){
	
	for (int i = 0; i < MAX; i++){
		if (palabra[i] == '\n'){
			palabra[i] = '\0';
		}
	}
}

void add_PlayList(){
    int index;
    index=0;
    for(int i = 0; i < 3 && index == 0 ; i++){
        if(C_PlayList[i].lleno_Playlist == 0){
            printf("\nIntroduce un nombre para la PlayList:\n");
            fflush(stdin);
            fgets(C_PlayList[i].nombre_PlayList,MAX,stdin);
            cambio(C_PlayList[i].nombre_PlayList);
            C_PlayList[i].lleno_Playlist=1;
            index=1;//para solo ingresar una vez
            
        }
        
    }
    if(index==0){
       printf("\n No queda ningun espacio libre para ninguna PlayList\n"); 
    }
}

