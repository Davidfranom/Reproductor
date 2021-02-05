/**
 * @file Playlist.h
 *
 * @brief API para el TAD Playlist
 *
 *   Este archivo contiene la API del nuestro tipo abstracto de nivel superior
 *   llamado Playlist el cual sirve como un contenedor de canciones enlazadas
 *   una con otra; estan todas las funciones con las cuales trabaja este TAD
 *
 * @author Daniel Gonzalez -> Equipo 1 EDA 1
 *
 * @date 04/02/2021
 *
 */

#ifndef  PLAYLIST_INC
#define  PLAYLIST_INC


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Track.h"


/**
 * Esta estructura Node representa a un nodo de una lista
 * circular doblemente enlazada, el campo Track datos es
 * tiene como proposito almacenar una canción que esta
 * representada por la estructura Track, y los apuntadores
 * next y prev ayudan a conectar un nodo con otro y asi generar
 * a la playlist
 */

typedef struct Node{

	Track datos;
	struct Node* next;
	struct Node* prev;
} Node;


/**
 * La estructura Playlist representa a una lista circular
 * doblemente enlazada, la cual funcionara como una Playlist
 * teniendo apuntadores a nodos, los cuales contienen las canciones
 * el campo name funciona como contenedor para el nombre de la
 * playlist, los apuntadores first, last y cursor sirven para
 * movernos por medio de la playlist, saber donde empieza y donde
 * acaba y el campo len sirve para llevar el conteo de cuantos
 * nodos han sido ingresados a la lista
 */

typedef struct Playlist
{
    char name[MAX];
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;

} Playlist;


Playlist* Playlist_New(          char name[]);
void      Playlist_Delete(       Playlist** this );
void      Playlist_Insert_front( Playlist* this, Track* x );
void      Playlist_Insert_back(  Playlist* this, Track* x );
void      Playlist_Insert(       Playlist* this, Track* x );
void      Playlist_Remove_front( Playlist* this );
void      Playlist_Remove_back(  Playlist* this );
void      Playlist_Remove(       Playlist* this );
Track*    Playlist_Get(          Playlist* this );
void      Playlist_Cursor_front( Playlist* this );
void      Playlist_Cursor_back(  Playlist* this );
void      Playlist_Cursor_next(  Playlist* this );
void      Playlist_Cursor_prev(  Playlist* this );
bool      Playlist_IsEmpty(      Playlist* this );
size_t    Playlist_Len(          Playlist* this );
void      Playlist_MakeEmpty(    Playlist* this );
void      Playlist_Traverse(     Playlist* this, void (*fn)( Track item,size_t c  ) );
void      Playlist_GralRemove(   Playlist* this, size_t id );
size_t    Playlist_GetID(        Playlist* this);
char*     Playlist_GetName(      Playlist* this);
void      Print_PlaylistName(    Playlist item, size_t c);

#endif
