#include "Track.h"


Track* Track_New(size_t id)
{
    Track* song = malloc( sizeof(Track) );

    if( song ){
    	song->id=id;
        Track_ChangeTitle(     song );
        //Track_ChangePerformer( song );
        //Track_ChangeGenre(     song );
        //Track_ChangeYear(      song );
        //Track_ChangeDuration(  song );
    } else{
        free( song );
        song = NULL;
        exit(1);
    }

    return song;
}


void Track_Delete( Track** this )
{
    assert( *this );

    free( *this );
    *this = NULL;

}

void Track_ChangeTitle( Track* this )
{
    printf("\nNombre de la cancion: ");
    //fflush( stdin );
    fgets(this->title,MAX,stdin);
    fgets(this->title,MAX,stdin);
    //scanf("%[^\n]",this->title);
    //gets(this->title);
    //printf("Nuevo nombre: %s ", this->title );
}

void Track_ChangePerformer( Track* this )
{
    printf("Artista: ");
    //fflush( stdin );
    fgets(this->performer,MAX,stdin);
    fgets(this->performer,MAX,stdin);
    //scanf("%[^\n]",this->performer);
    //gets( this->performer );
    //printf("Nombre del artista: %s ", this->performer );
}

void Track_ChangeGenre( Track* this )
{
    printf("Genero: ");
    //fflush( stdin );
    fgets(this->genre,MAX,stdin);
    fgets(this->genre,MAX,stdin);
    //scanf("%[^\n]",this->genre);
    //gets( this->genre );
    //printf("Nombre del genero: %s ", this->genre );
}

void Track_ChangeYear( Track* this )
{
    printf("Año: ");
    fflush( stdin );
    scanf("%d", &this->year );
    //printf("Año de salida: %d ", this->year );
}

void Track_ChangeDuration( Track* this )
{
    printf("Duración: ");
    fflush( stdin );
    scanf("%f", &this->duration );
    //printf("Tiempo de duración: %lf ", this->duration );
}


void Print_DataTrack( Track* this )
{
    printf("\n\tDatos de la canción:\n\n");
    printf("Nombre: %s\n", this->title );
    printf("Artista: %s\n", this->performer );
    printf("Genero: %s \n", this->genre );
    printf("Año de salida: %d \n", this->year );
    printf("Tiempo de duración: %0.2f min \n\n", this->duration );
}

char* Track_GetTitle(Track* this){
	assert(this);
	return (char*)this->title;
}
float Track_GetDuration(Track* this){
	assert(this);
	return this->duration;
}

//Para Traverse
void Print_TrackTitle(Track item,size_t c){
	printf("%ld. %s\n",c,item.title);
}



/*Funciones de Erandi
Track New_Track()
{
        Track New_Track;
        printf("\nNombre de la cancion:");
        fflush(stdin);
        gets(New_Track.title);

        printf("\nNombre del artista: ");
        fflush(stdin);
        gets(New_Track.performer);

        printf("\nGenero de la cancion: ");
        fflush(stdin);
        gets(New_Track.genre);

        printf("\nIngrese el año: ");
        fflush(stdin);
        scanf("%d",&New_Track.year);

        printf("\nIngrese la duracion: ");
        fflush(stdin);
        scanf("%f",&New_Track.duration);

        return New_Track;
}


void imprimir_cancion(Track mostrar_cancion)
{
    printf("Cancion:%s\n",mostrar_cancion.title);
    printf("Artista:%s\n",mostrar_cancion.performer);
    printf("Genero musical:%s\n",mostrar_cancion.genre);
    printf("Año:%d\n",mostrar_cancion.year);
    printf("Duracion:%f\n",mostrar_cancion.duration);

}

*/
