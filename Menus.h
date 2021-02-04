#ifndef Menus_INC
#define Menus_INC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Track.h"
#include "Playlist.h"

#include "Player.h"


void  Clear();  //Creamos esta funci�n ya que se llamara continuamente pero funciona de forma diferente en windows y linux
void  PrintMenuPrincipal(Player* this,Playlist* that);
void  PrintMenuPlaylist(Playlist* this);
void PrintMenuCancion(Playlist* this, bool play);
void  TestMenuPlaylist( Player* player, Playlist* this,Playlist* that); //Deberia de pasarse una playlist en la que se guardara o modificaran canciones
void  TestPrincipal();


#endif // Menus_INC
