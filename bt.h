#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <iso646.h>
// para and, or y not

#include "Stack.h"
#include "Array.h"
#include "Playlist.h"

bool es_factible (int c, int p, int acum);
bool es_solucion (int p, int acum);
void bt( Array* candidatos, Stack* solucion,Stack* posicion, int p, int* acum, Stack* best,Stack* b_posicion,size_t opt );
int cambio( Array* candidatos, Stack* solucion,Stack* posicion, int p );
void backtracking(Playlist* playlist_gral,Playlist* this,int limit);
