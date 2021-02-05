#ifndef Track_INC
#define Track_INC

#define MAX 80

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Track
{
	size_t id;
    char  title[ MAX ];
	char  performer[ MAX ];
	char  genre[ MAX ];
	int   year;
	int duration;

} Track;

bool 	validar(char* this);
Track*  Track_New(size_t id);
void    Track_Delete(           Track** this );
void    Track_ChangeTitle(      Track* this );    //Funciones particulares
void    Track_ChangePerformer(  Track* this );
void    Track_ChangeGenre(      Track* this );
void    Track_ChangeYear(       Track* this );
void    Track_ChangeDuration(   Track* this );
void    Print_DataTrack(        Track* this );

char*   Track_GetTitle(Track* this);
int Track_GetDuration(Track* this);

void Print_TrackTitle(Track item,size_t c);






#endif // Track_INC
