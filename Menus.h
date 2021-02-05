/**
 * @file Menus.h
 *
 * @brief Módulo para los menús
 *
 * Este archivo contiene el modulo para los menús, es decir contiene las
 * funcione que permiten activar los menús, desplazarse entre ellos y, en
 * general, generan la interfaz que el usuario final visualiza, manipula
 * un contenedor de listas (lista de listas) y una lista "general" que
 * incluye canciones ingresadas al hazar que no necesariamente pertenecen
 * a una Playlist particular.
 *
 * @author Daniel Gonzalez y David Ortiz -> Equipo 1 EDA 1
 *
 * @date 04/02/2021
 *
 */


#ifndef Menus_INC
#define Menus_INC

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Track.h"     //Modulos para TAD's y algoritmo de BT
#include "Playlist.h"
#include "bt.h"
#include "Player.h"


void  Clear();
void  PrintMenuPrincipal( Player* this, Playlist* that );
void  PrintMenuPlaylist( Playlist* this );
void  PrintMenuCancion( Playlist* this, bool play );
void  TestMenuPlaylist( Player* player, Playlist* this, Playlist* that );
void  TestPrincipal();
void  TestMenuCancion(Playlist* this);


#endif // Menus_INC
