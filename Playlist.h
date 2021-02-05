#ifndef  PLAYLIST_INC
#define  PLAYLIST_INC

#include <stdlib.h>
#include <stdio.h>

#include <assert.h>
#include "Track.h"

typedef struct Node{

	Track datos;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct Playlist{
    char name[MAX]; //Nombre del playlist, en prueba
    
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;

} Playlist;

Playlist* Playlist_New(char name[]);
void Playlist_Delete( Playlist** this );

void Playlist_Insert_front( Playlist* this, Track* x );
void Playlist_Insert_back( Playlist* this, Track* x );
void Playlist_Insert( Playlist* this, Track* x );

void Playlist_Remove_front( Playlist* this );
void Playlist_Remove_back( Playlist* this );
void Playlist_Remove( Playlist* this );

Track* Playlist_Get( Playlist* this );

void Playlist_Cursor_front( Playlist* this );
void Playlist_Cursor_back( Playlist* this );
void Playlist_Cursor_next( Playlist* this );
void Playlist_Cursor_prev( Playlist* this );

bool Playlist_IsEmpty( Playlist* this );
size_t Playlist_Len( Playlist* this );

void Playlist_MakeEmpty( Playlist* this );
void Playlist_Traverse( Playlist* this, void (*fn)( Track item,size_t c  ) );
void Playlist_GralRemove( Playlist* this, size_t id );
size_t Playlist_GetID(Playlist* this);

char* Playlist_GetName(Playlist* this);

void Print_PlaylistName(Playlist item,size_t c); 

#endif
