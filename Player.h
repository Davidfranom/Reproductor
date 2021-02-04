#ifndef  PLAYER_INC
#define  PLAYER_INC

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "Playlist.h"

typedef struct Node_2{

	Playlist datos;
	struct Node_2* next;
	struct Node_2* prev;
} Node_2;

typedef struct Player{
    char name[100]; //Nombre del Player, en prueba
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
