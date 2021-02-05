#ifndef Track_INC
#define Track_INC

#define MAX 80

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>


/**
 * Esta estructura Track represenata a un objeto, en este caso una canción
 * ,la estructura contiene un campo id para identificar a cada canción más
 * facilmente y es unica para cada una, title almacena su nombre, performer
 * el artista, genre al genero, year el año de salida de la canción y duration
 * la duración en minutos enteros, no divisibles, de la canción todos los campos
 * son modificados mediante funciones y otras permiten obtener datos del objeto
 * por lo que es considerado un TAD
 */

typedef struct Track
{
	size_t id;
    char   title[ MAX ];
	char   performer[ MAX ];
	char   genre[ MAX ];
	int    year;
	int    duration;

} Track;

bool 	validar(                char* this );
Track*  Track_New(              size_t id );
void    Track_Delete(           Track** this );
void    Track_ChangeTitle(      Track* this );
void    Track_ChangePerformer(  Track* this );
void    Track_ChangeGenre(      Track* this );
void    Track_ChangeYear(       Track* this );
void    Track_ChangeDuration(   Track* this );
void    Print_DataTrack(        Track* this );
char*   Track_GetTitle(         Track* this);
int     Track_GetDuration(      Track* this);
void    Print_TrackTitle(       Track item, size_t c );






#endif // Track_INC
