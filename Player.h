/**
 * @file Player.h
 *
 * @brief Contiene las declaraciones de las funciones para el TAD Player que es una lista 
 * 
 *
 * Player es un TAD que sirve de lista enlazada, 
 * cuyos nodos contienen como elemento de datos otra lista de distinto tipo.
 *
 * @autores David Ortiz
 * @date 04/02/21
 * @version 1
 */

#ifndef  PLAYER_INC
#define  PLAYER_INC

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Playlist.h"

//! Define un tipo compuesto Node_2 para usarlo en listas enlazadas
typedef struct Node_2{

	Playlist datos; /*! datos es de tipo Playlist que a su vez es un TAD */
	struct Node_2* next;
	struct Node_2* prev;
} Node_2;

//! Define un tipo compuesto Player para usarlo como lista enlazada
typedef struct Player{
    char name[100]; /*! EL nombre de la lista Player*/
	Node_2* first;
	Node_2* last;
	Node_2* cursor;
	size_t len;

} Player;

Player* Player_New();
void Player_Delete( Player** this );

void Player_Insert_front( Player* this, Playlist* x );
void Player_Insert_back( Player* this, Playlist* x );
void Player_Insert( Player* this, Playlist* x );

void Player_Remove_front( Player* this );
void Player_Remove_back( Player* this );
void Player_Remove( Player* this );

Playlist* Player_Get( Player* this );

void Player_Cursor_front( Player* this );
void Player_Cursor_back( Player* this );
void Player_Cursor_next( Player* this );
void Player_Cursor_prev( Player* this );

bool Player_IsEmpty( Player* this );
size_t Player_Len( Player* this );

void Player_MakeEmpty( Player* this );
void Player_Traverse( Player* this, void (*fn)( Playlist item, size_t c  ) );
void Player_GralRemove( Player* this, size_t id ); 

#endif
