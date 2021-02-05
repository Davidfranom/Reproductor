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
* @param id El identificador de la canci�n
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
* @brief Elimina una canci�n
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
* @brief Cambia el t�tulo de la canci�n
* @param Track Una referencia a una canci�n
* @return void No devuelve nada
*/
void Track_ChangeTitle( Track* this )
{
    printf("\nNombre de la canci�n: ");

    //fflush( stdin );     //Estas se consideraron para windows y funcionaban
    //gets(this->title);   //pero en linux generaban errores

    fgets( this->title, MAX, stdin );
    scanf("%[^\n]", this->title );

}


/**
* @brief Cambia el artista de la canci�n
* @param Track Una referencia a una canci�n
* @return void No devuelve nada
*/
void Track_ChangePerformer( Track* this )
{
    printf("Artista: ");
    fgets( this->performer, MAX, stdin );
    scanf("%[^\n]", this->performer);
}


/**
* @brief Cambia el g�nero de la canci�n
* @param Track Una referencia a una canci�n
* @return void No devuelve nada
*/
void Track_ChangeGenre( Track* this )
{
    printf("G�nero: ");
    fgets(this->genre,MAX,stdin);
    scanf("%[^\n]",this->genre);
}


/**
* @brief Cambia el a�o de la canci�n
* @param Track Una referencia a una canci�n
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
        printf("Opci�n inv�lida!\n");
        Track_ChangeYear( this );
    }
}


/**
* @brief Cambia la duraci�n de la canci�n
* @param Track Una referencia a una canci�n
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
        printf("Opci�n inv�lida!\n");
        Track_ChangeDuration( this );
    }

}



/**
* @brief Imprime los datos de la canci�n
* @param Track Una referencia a una canci�n
* @return void No devuelve nada
*/
void Print_DataTrack( Track* this )
{
    printf("\n\tDatos de la canci�n:\n\n");
    printf("Nombre: %s\n", this->title );
    printf("Artista: %s\n", this->performer );
    printf("G�nero: %s \n", this->genre );
    printf("A�o de salida: %d \n", this->year );
    printf("Tiempo de duraci�n: %d min \n\n", this->duration );
}


/**
* @brief Obtiene el t�tulo de la canci�n
* @param Track Una referencia a una canci�n
* @return char devuelve el t�tulo de la canci�n
*/
char* Track_GetTitle(Track* this){
	assert(this);
	return (char*)this->title;
}

/**
* @brief Obtiene el t�tulo de la canci�n
* @param Track Una referencia a una canci�n
* @return float devuelve la duraci�n de la canci�n
*/
int Track_GetDuration(Track* this){
	assert(this);
	return this->duration;
}


/**
* @brief Imprime el t�tulo de la canci�n
* @param Track Recibe una canci�n
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
