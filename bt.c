/*Copyright (C) 
 * 2018 - eda1 dot fiunam at yahoo dot com dot mx
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

/* 2020-2 */

/* 1. Cambie el nombre de este archivo a cambio_best.c
 * 2. Compile con:
 *    gcc -Wall -std=c99 -osalida.out cambio_best. Stack.c Array.c
 * 3. Ejecute con:
 *    ./salida.out
 */


#include "bt.h"


bool es_factible (int c, int p, int acum)
{
   return (c+acum) <= p;
}

bool es_solucion (int p, int acum)
{
   return (acum == p);
}


void bt( Array* candidatos, Stack* solucion,Stack* posicion, int p, int* acum, Stack* best,Stack* b_posicion,size_t opt )
{
	for(size_t x=opt;x<(Array_len(candidatos));++x){
		opt=x+1;
		if (es_factible(Array_get(candidatos,x),p,*acum)){
			Stack_Push(solucion,Array_get(candidatos,x));
			Stack_Push(posicion,x);
			*acum+=Array_get(candidatos,x);
			if(es_solucion(p,*acum)){
				if(Stack_Len(solucion)>Stack_Len(best)){
					Stack_Copy(best,solucion);
					Stack_Copy(b_posicion,posicion);
				}
				*acum-=Stack_Pop(solucion);
				Stack_Pop(posicion);
			} else{
				bt(candidatos,solucion,posicion,p,acum,best,b_posicion,opt);
			}
		} else{
		}
	}
	if(Stack_IsEmpty(solucion)==false){
		*acum-=Stack_Pop(solucion);
		Stack_Pop(posicion);
	}
}


int cambio( Array* candidatos, Stack* solucion,Stack* posicion, int p )
{
Stack* best=Stack_New(Stack_Capacity(solucion));
Stack* b_posicion=Stack_New(Stack_Capacity(posicion));
/*for (size_t i=0;i<Stack_Capacity(best);++i){
Stack_Push(best,0);
}*/
 int acum = 0;
 size_t opt=0;
 bt( candidatos, solucion,posicion, p, &acum, best,b_posicion,opt);
 //if(Stack_Len(best)!=Stack_Capacity(solucion)-1){
Stack_Copy(solucion,best);
Stack_Copy(posicion,b_posicion);
return Stack_Len(solucion);
//}
Stack_Delete( best );
Stack_Delete(b_posicion);
}



void backtracking(Playlist* playlist_gral,Playlist* this,int limit)
{
   Array* candidatos = Array_new( Playlist_Len(playlist_gral) );
   
	Playlist_Cursor_front(playlist_gral);
	for(size_t i=0;i<Playlist_Len(playlist_gral);++i){
		Array_set( candidatos, i, Track_GetDuration(Playlist_Get(playlist_gral)) );
		Playlist_Cursor_next(playlist_gral);
	}
	
	/*
   Array_set( candidatos, 0, 5 );
   Array_set( candidatos, 1, 2 );
   Array_set( candidatos, 2, 1 );
   Array_set( candidatos, 3, 4 );
   Array_set( candidatos, 4, 4 );
   Array_set( candidatos, 5, 1 );
   Array_set( candidatos, 6, 1 );
   Array_set( candidatos, 7, 3 );
   */

	int p = limit;

   Stack* solucion = Stack_New( p );
   Stack* posicion = Stack_New(p);
   // el peor caso es dar p canciones de 1 peso, lo cual siempre va a suceder, por
   // eso la pila debe tener al menos esa capacidad
	

   int num_canciones = cambio( candidatos, solucion,posicion, p );

   if( num_canciones > 0 ){
   	
		printf("\nPlaylist %s optimizada\n",Playlist_GetName(this));
      printf( "(%d) canciones: ", num_canciones );
		int tot=0;
      while( not Stack_IsEmpty( solucion ) ){
          tot+=Stack_Pop( solucion );
      }
      printf("%d minutos\n",tot);
      
      //printf("Stack len posicion: %d\n",Stack_Len(posicion));
      while( not Stack_IsEmpty( posicion ) ){
      	//Coloca al cursor en posicion
      	Playlist_Cursor_front(playlist_gral);
      	size_t pos=Stack_Pop( posicion );
        for(size_t i=0;i<pos;++i){
            Playlist_Cursor_next(playlist_gral);
        }
        //Playlist_Cursor_prev(playlist_gral);
        //////////////////////////////////
    
        Playlist_Insert_back( this, Playlist_Get(playlist_gral) );
      }
      Playlist_Traverse(this,Print_TrackTitle);


      printf( "\n" );

   } else{ 
   		
   		//printf ("No se encontró ninguna solución\n"); 
   		if(p>0){
   			p--;
   			backtracking (playlist_gral,this,p);
   		} else{
   			printf ("No se encontró ninguna solución\n"); 
   		}	
   }

   Array_delete( &candidatos );
   Stack_Delete( solucion );
   solucion = NULL;


}

