#include <stdio.h>
#include <stdlib.h>
#include "CDLL.h"


void PrintMenuPrincipal()
{
    printf("\n\tMen� principal\n");
    printf("A) Lista de canciones completa\n");
    printf("N) Nueva Playlist\n");
    printf("D) Eliminar Playlist\n");
    printf("R) Reproducir Playlist\n");
    printf("E) Salir\n");
    printf("H) Mostrar menu\n ");
}

void PrintMenuPlaylist()
{
    printf("A) Agregar canci�n\n");
    printf("R) Remover canci�n\n");
    printf("I) Reproducir canci�n\n");
    printf("S) Salir\n");
}


//Activaci�n de Segundo men�
void TestMenuPlaylist() //Deberia de pasarse una playlist en la que se guardara o modificaran canciones
{
    char cmd;
    char str[80];

    PrintMenuPlaylist();

    do{
        printf("cmd > > >: ");
        scanf( "%s", &str );
        cmd = str[0];

        switch( cmd )
        {
            case 'S': case 's':   break;

            case 'A': case 'a':
                //Se crea al objeto cancion
                /*Track* song = */
                 Track v2 = New_Track();
                imprimir_cancion(v2);
                /*CDLL_Insert( this, song ); */  //Verificar que se guarde en la Playlist (una CDLL)


            break;

            case ' R': case 'r':
            break;

            case 'I': case 'i':
            break;

            default:
                printf("Opci�n invalida!\n");
                PrintMenuPlaylist();
            break;

        }

    } while( cmd != 'S' && cmd != 's');
}


//Activaci�n de men� "principal"
void TestPrincipal()
{
    char cmd;
    char str[80];

    PrintMenuPrincipal();


    do{
        printf("cmd > > >: ");
        scanf("%s", &str );
        cmd = str[ 0 ];

        switch( cmd )
        {
            case 'E': case 'e': break;
            case 'H': case 'h': PrintMenuPrincipal(); break;

            case 'A': case 'a':
                //en progreso
            break;

            case 'N': case 'n':
                printf("\nNombre del Playlist: ");
                char name[50];
                scanf("%c", name);
                //Playlist* p1 = CDLL_New( name );
                //printf("%c", p1->name);
                //Playlist_Delete(&p1);
            break;

            case 'D': case 'd':
                //Funcion mostrar playlist's

            break;

            case 'R': case 'r':

            break;

            default:
                printf("Comando inv�lido\n");
                PrintMenuPrincipal();
            break;


        }


    } while( cmd != 'E' && cmd != 'e');

}

/*
void Print( int item )
{
	printf( "%d\n", item );
}*/

int main()
{
    TestMenuPlaylist();
}
