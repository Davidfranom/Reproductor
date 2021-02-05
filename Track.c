/**
* @file Track.c
*
* @brief Define las funciones de Track
*
* @author Equipo 1 EDA 1
*
* @date 04/02/2021
*
*/


#include "Track.h"


/**
* @brief Crea un objeto Track
* @param id El identificador de la canción
* @return song Regresa una nueva Track
*/
Track* Track_New(size_t id)
{
    Track* song = malloc( sizeof(Track) );

    if( song ){
    	song->id=id;
        Track_ChangeTitle(     song );
        Track_ChangePerformer( song );
        Track_ChangeGenre(     song );
        Track_ChangeYear(      song );
        Track_ChangeDuration(  song );
    } else{
        free( song );
        song = NULL;
        exit(1);
    }

    return song;
}



/**
* @brief Elimina una canción
* @param Track Referencia a una referencia de una cancion
* @return void No devuelve nada
*/
void Track_Delete( Track** this )
{
    assert( *this );

    free( *this );
    *this = NULL;

}


/**
* @brief Cambia el título de la canción
* @param Track Una referencia a una canción
* @return void No devuelve nada
*/
void Track_ChangeTitle( Track* this )
{
    printf("\nNombre de la canción: ");

    //fflush( stdin );     //Estas se consideraron para windows y funcionaban
    //gets(this->title);   //pero en linux generaban errores

    fgets( this->title, MAX, stdin );
    scanf("%[^\n]", this->title );

}


/**
* @brief Cambia el artista de la canción
* @param Track Una referencia a una canción
* @return void No devuelve nada
*/
void Track_ChangePerformer( Track* this )
{
    printf("Artista: ");
    fgets( this->performer, MAX, stdin );
    scanf("%[^\n]", this->performer);
}


/**
* @brief Cambia el género de la canción
* @param Track Una referencia a una canción
* @return void No devuelve nada
*/
void Track_ChangeGenre( Track* this )
{
    printf("Género: ");
    fgets(this->genre,MAX,stdin);
    scanf("%[^\n]",this->genre);
}


/**
* @brief Cambia el año de la canción
* @param Track Una referencia a una canción
* @return void No devuelve nada
*/
void Track_ChangeYear( Track* this )
{
    char optChar[MAX];
    scanf("%s", optChar );

    if( validar( optChar ) ){
        int opt = atoi(optChar);
        this->year = opt;

    } else{
        printf("Opción inválida!\n");
        Track_ChangeYear( this );
    }
}


/**
* @brief Cambia la duración de la canción
* @param Track Una referencia a una canción
* @return void No devuelve nada
*/
void Track_ChangeDuration( Track* this )
{
    char optChar[MAX];
    scanf("%s", optChar );

    if( validar( optChar ) ){
        int opt = atoi(optChar);
        this->duration = opt;

    } else{
        printf("Opción inválida!\n");
        Track_ChangeDuration( this );
    }

}



/**
* @brief Imprime los datos de la canción
* @param Track Una referencia a una canción
* @return void No devuelve nada
*/
void Print_DataTrack( Track* this )
{
    printf("\n\tDatos de la canción:\n\n");
    printf("Nombre: %s\n", this->title );
    printf("Artista: %s\n", this->performer );
    printf("Género: %s \n", this->genre );
    printf("Año de salida: %d \n", this->year );
    printf("Tiempo de duración: %d min \n\n", this->duration );
}


/**
* @brief Obtiene el título de la canción
* @param Track Una referencia a una canción
* @return char devuelve el título de la canción
*/
char* Track_GetTitle(Track* this){
	assert(this);
	return (char*)this->title;
}

/**
* @brief Obtiene el título de la canción
* @param Track Una referencia a una canción
* @return float devuelve la duración de la canción
*/
int Track_GetDuration(Track* this){
	assert(this);
	return this->duration;
}


/**
* @brief Imprime el título de la canción
* @param Track Recibe una canción
* @param c Un contador o identificador
* @return void No devuelve nada
*/
//Para Traverse
void Print_TrackTitle(Track item,size_t c){
	printf("%ld. %s\n",c,item.title);
}


/**
* @brief valida si dos cadenas de caracteres son identicas
* @param una referencia a una cadena de caracteres
* @return bool Verdadero si es identica, Falso si no lo es
*/
bool validar(char* this){
    bool res=true;
    size_t c=0;
    while(this[c]!='\0'){
        int i=isdigit(this[c]);
        c++;

        //printf("%d\n",i);

        if(i==0){
            res=false;
            break;
        }

    }

    return res;
}
