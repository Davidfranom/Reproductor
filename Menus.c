#include "Menus.h"
#define WIN
void Print_TrackTitle(Track item,size_t c){
	printf("%ld. %s\n",c,item.title);
}
void Print_PlaylistName(Playlist item,size_t c){
	printf("%ld. %s\n",c,item.name);
}
void Clear()
{
    #ifdef WIN
        system( "cls" ); //Limpia la pantalla en windows
    #endif

    #ifdef LIN

        system( "clear ");   //Limpia la pantalla en Linux
    #endif // LIN
}

void PrintMenuPrincipal(Player* this,Playlist* that)

{
	printf("\nReproductor (%d playlists)(%d canciones)\n",Player_Len(this),Playlist_Len(that));
	
    printf("\n\tMen� principal\n");
    printf("A) Lista de canciones completa\n");    //Mostraria todas las canciones de la lista principal
    printf("N) Nueva Playlist\n");                 //Crearia una nueva playlist y la almacenaria en la lista secundaria
    printf("D) Eliminar Playlist\n");              //Eliminaria una playlist contenida en la lista secundaria
    printf("R) Abrir Playlist\n");            //Mostraria un menu con opciones para una playlist
    printf("C) Limpiar pantalla\n");
	printf("E) Salir\n");                          //Salimos del programa de manera defenitiva

    printf("H) Mostrar ayuda\n ");                  //Vuelve a mostrar este mensaje


}

void PrintMenuPlaylist(Playlist* this)
{
	
	printf("\nPlaylist: %s (%d canciones)\n",this->name,Playlist_Len(this));
	
    printf("\n\tMen� para Playlist\n");
    printf("A) Agregar canci�n\n");       //Agrega una canci�n a la playlist en la que se este trabajando
    printf("X) Remover canci�n\n");       //Quita una canci�n seleccionada por el usuario
    printf("P) Reproducir canci�n\n");    //Simula la reproducci�n de la canci�n ( aun falta un detalle)
    printf("H) Mostrar ayuda\n");         //Vuelve a mostrar este men�
    //printf("T) Mostrar canciones\n");
    printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");                 //Salimos de este men� y regresamos al principal
}

// Funci�n de activaci�n de segundo men�

void TestMenuPlaylist( Player* player, Playlist* this, Playlist* that) //Deberia de pasarse una playlist en la que se guardara o modificaran canciones
{
    Clear();
    char cmd;
    char str[80];

    PrintMenuPlaylist(this);

    do{
    	//Clear();
    	//PrintMenuPlaylist(this);
        printf("\ncmd > > >: ");
        scanf( "%s", &str );
        cmd = str[0];

        switch( cmd )
        {
        	case 'C': case 'c': Clear(); PrintMenuPlaylist(this); break;
        	/*case 'T': case 't': 
        		Playlist_Traverse(this,Print_TrackTitle);
        	break;*/
            case 'S': case 's':   break;
            case 'H': case 'h': PrintMenuPlaylist(this); break;


            case 'A': case 'a':;   //";" corrige el error de compilaci�n

                /*if( Playlist_Len( this ) > 0 ){
                    Playlist_Cursor_back( this );  //Cambiado por un Insert_back
                }*/
                Track *v1 = Track_New();
                Playlist_Insert_back( this, v1 ); printf("\nInsertando %s en %s...\n",v1->title,this->name);
                Playlist_Insert_back(that,v1);
                //Print_DataTrack( v1 );
                Track_Delete( &v1 );  /*Es interesante y valido borrar la cancion despues de crearla puesto
                                            que utilizamos a la funcion Playlist_Insert, insertandola en la playlist
                                            que se paso por direccion, por lo tanto ya queda guardada y se cumplen
                                            esos dos propositos, guardarla en una playlist y no dejar memory leaks */
                PrintMenuPlaylist(this);

            break;


            case 'X': case 'x':
                if( Playlist_IsEmpty( this ) == true ){
                    printf("\n��� Error !!! , la playlist esta vacia\n");
                    break;
                } else{
                    Clear();
                    printf("\n\t Eliga la canci�n que sera removida:\n");
                    Playlist_Cursor_front( this );

                    for( size_t i = 0; i<Playlist_Len( this ); ++i ){
                        printf("%d.- ",i+1); puts( this->cursor->datos.title ); //Mostramos la lista de canciones en la playlist
                        Playlist_Cursor_next( this );
                    }

                    size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%ld", &p );

                    Playlist_Cursor_front( this );

                    if( p == 1){
                        printf("Removiendo "); puts( this->cursor->datos.title); printf("...\n");
                        Playlist_Remove_front( this );

                    } else{

                        for( size_t i = 0; i< p-1; ++i ){
                            Playlist_Cursor_next( this );
                        }
                        printf("Removiendo "); puts( this->cursor->datos.title);
                        Playlist_Remove( this );

                    }

                }

                //Faltaria escoger una cancion, y nosotros la eliminamos ya sea agregando un indice
                //o recorriendo la lista desde el primer nodo hasta el "numero" escogido por el usuario:
                // !!!Actualizaci�n, ya QUEDO RESUELTO


            break;

            case 'P': case 'p':

                if( Playlist_IsEmpty( this ) == true ){
                    printf("\n��� Error !!! , la playlist esta vacia\n");
                    break;
                } else{
                	Playlist_Traverse(this,Print_TrackTitle);
                    /*Playlist_Cursor_front( this );
                    for( size_t i = 0; i<Playlist_Len( this ); ++i ){
                        printf("%d.- ",i+1); puts( this->cursor->datos.title );  //Mostramos la lista de canciones en la playlist
                        Playlist_Cursor_next( this );
                    }*/

                    size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%ld", &p );

                    Playlist_Cursor_front( this );

                    if( p == 1){
                        printf("Reproduciendo "); puts( this->cursor->datos.title); printf("...\n");
                        //Simulaci�n de la reproducci�n, �Como hacer siguiente cancion, anterior y
                        //que haya un cierto tiempo antes de la siguiente instruccion?

                    } else{

                        for( size_t i = 0; i< p-1; ++i ){
                            Playlist_Cursor_next( this );
                        }
                        printf("Reproduciendo "); puts( this->cursor->datos.title);
                    }
                    Track t=Playlist_Get(this);
                    Print_DataTrack(&t);
                    

                }

                //Faltaria escoger una cancion, y nosotros simulamos la reproducci�n, ya sea agregando un indice
                //o recorriendo la lista desde el primer nodo hasta el "numero" escogido por el usuario

                // !!!ACTUALIZACI�N: El usuario ya puede escoger la canci�n, pero podria buscarse la forma
                // de hacer "mas detallada" la simulaci�n de la reproducci�n

				PrintMenuPlaylist(this);
            break;

            default:
                printf("Opci�n invalida!\n");
                PrintMenuPlaylist(this);
            break;

        }

    } while( cmd != 'S' && cmd != 's');
}

void TestPrincipal()
{
    char cmd;
    char str[80];
    /*  Se pueden crear dos listas doblemente enlazadas
        la primera para guardar las canciones favoritas sin necesidad
        de estar almacenadas en una playlist y la segunda serviria como
        contenedor de varias playlist's
    */

	

	Player* player=Player_New();
	Playlist* playlist_gral=Playlist_New();

    PrintMenuPrincipal(player,playlist_gral);

    do{
    	//Clear();
    	//PrintMenuPrincipal(player);
        printf("\ncmd > > >: ");
        scanf("%s", &str );
        cmd = str[ 0 ];

        switch( cmd )
        {
        	case 'C': case 'c': Clear(); PrintMenuPrincipal(player,playlist_gral); break;
            case 'E': case 'e': break;
            case 'H': case 'h': PrintMenuPrincipal(player,playlist_gral); break;

            case 'A': case 'a':
                //en progreso
            break;

            case 'N': case 'n':
                printf("\nNombre del Playlist: ");

                char name[MAX];
                
                fflush( stdin );
                gets(name);
                
                //scanf("%s", name);
                Playlist* p1 = Playlist_New( name );
                //printf("%s\n", p1->name);
                
                Player_Insert_back(player,p1);
                
                printf("Insertando la playlist %s... \n",name);
                PrintMenuPrincipal(player,playlist_gral);
                
                
                Playlist_Delete(&p1);
            break;

            case 'D': case 'd':
                //Funcion mostrar playlist's

            break;

            case 'R': case 'r':
            	
            	assert(!Player_IsEmpty(player));
            	
            	
            	printf("\nElija una playlist\n");
            	int opt;
            	
            	
            	Player_Traverse(player,Print_PlaylistName);
            	
            	printf("\ncmd > > >: ");
            	
            	scanf("%d",&opt);
            	
            	Player_Cursor_front(player);
            	for(size_t i=0;i<opt;++i){
            		Player_Cursor_next(player);
            	}
            	Player_Cursor_prev(player);
            	
                 {
                    //Playlist* this = Playlist_New();
                    //strcpy(this->name,Player_Get(player).name);
                    
                    
                    
                    TestMenuPlaylist(player,&player->cursor->datos,playlist_gral);
                    
                    //player->cursor->datos=*this;
                    
                    //Playlist_Traverse(player->cursor,Print_TrackTitle);
                    
                    
                    //Playlist_Delete( &this );
                    PrintMenuPrincipal(player,playlist_gral);
                 }

            break;

            default:
                printf("Comando inv�lido\n");
                PrintMenuPrincipal(player,playlist_gral);
            break;


        }


    } while( cmd != 'E' && cmd != 'e');

    /* Una vez llegados a este punto es posible que el usuario ya
       ya haya elegido salir del programa, por lo tanto deberiamos
       devolver la memoria pedida por las primeras dos listas; con la
       primera no habria demasiado problema, con la segunda deberia
       devolverse la memoria de cada nodo, pero cada nodo es una
       playlist independiente y una vez que no existan nodos, devolver
       la del objeto en si mismo*/

       Playlist_Delete(&playlist_gral);
       Player_Delete(&player);


}
