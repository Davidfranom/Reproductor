#include "Menus.h"
#define LIN


/**
 * @brief Limpia la pantalla
 *
 * @pre La constante LIN permite que la función cumpla su proposito
 *      en Linux, definirla como WIN lo hace en Windows
 *
 * @post La pantalla debe limpiarse para mejorar el flujo de información
 */

void Clear()
{
    #ifdef WIN
        system( "cls" ); //Limpia la pantalla en windows
    #endif

    #ifdef LIN
        system( "clear ");   //Limpia la pantalla en Linux
    #endif // LIN
}



/**
 * @brief Imprime el Menú principal
 *
 * @param lista Referencia al contenedor de listas
 * @param lista Referencia al playlist "general"
 *
 * @pre Las listas deben existir
 */

void PrintMenuPrincipal(Player* this,Playlist* that)

{
	printf("\nReproductor (%ld playlists)(%ld canciones)\n",Player_Len(this),Playlist_Len(that));

    printf("\n\tMenú principal\n");
    printf("A) Lista de canciones completa\n");    //Mostraria todas las canciones de la lista principal
    printf("N) Nueva Playlist\n");                 //Crearia una nueva playlist y la almacenaria en la lista secundaria
    printf("Z) Nueva canción\n");
	printf("D) Eliminar Playlist\n");              //Eliminaria una playlist contenida en la lista secundaria
    printf("X) Eliminar canción\n");
	printf("R) Abrir Playlist\n");                 //Mostraria un menu con opciones para una playlist
	printf("C) Limpiar pantalla\n");
	printf("E) Salir\n");                          //Salimos del programa de manera defenitiva

}



/**
 * @brief Imprime el menú de opciones de playlist
 *
 * @param lista Referencia a una playlist en particular
 *
 * @pre La lista debe existir
 */

void PrintMenuPlaylist(Playlist* this)
{

	printf("\nPlaylist: %s (%ld canciones)\n",Playlist_GetName(this),Playlist_Len(this));

    printf("\n\tMenú para Playlist\n");
    printf("A) Agregar canción\n");         //Agrega una canción a la playlist en la que se este trabajando
    printf("X) Remover canción\n");         //Quita una canción seleccionada por el usuario
	printf("P) Reproducir canción\n");    	//Simula la reproducción de la canción ( aun falta un detalle)
    printf("O) Optimizar Playlist\n");
    printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");                 	//Salimos de este menú y regresamos al principal
}



/**
 * @brief Imprime el menú de opciones para la canción
 *
 * @param lista Referencia a una playlist en particular
 * @param true si la canción se esta "reproduciendo"
 *        false si la canción esta pausada
 *
 * @pre La lista debe existir
 * @pre La lista debe contener al menos una canción
 */

void PrintMenuCancion(Playlist* this,bool play)
{


	if(play){
		printf("\nReproduciendo: ");
	} else{
		printf("\nEn pausa: ");
	}


	printf("%s\n",Track_GetTitle(Playlist_Get(this)));//Aqui

	Print_DataTrack(Playlist_Get(this));

    printf("\n\tMenú para Canción\n");
    printf("R) Siguiente\n");
    printf("L) Anterior\n");
    printf("P) Pausar/Reproducir\n");
	printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");
}



/**
 * @brief Función de activación del tercer ménu
 *
 * @param lista Referencia a una playlist en particular
 *
 * @pre La lista debe existir
 * @pre La lista debe contener al menos una canción
 */
void TestMenuCancion(Playlist* this)
{
	Clear();
    bool play=true;
    char cmd;
    char str[80];

    do{
    	PrintMenuCancion(this,play);
        printf("\ncmd > > >: ");
        scanf( "%s", (char*)&str );
        cmd = str[0];

        switch( cmd )
        {
        	case 'C': case 'c': Clear();
			break;

            case 'S': case 's':
			break;

            case 'R': case 'r':
            	Playlist_Cursor_next(this);
			break;

            case 'L': case 'l':
            	Playlist_Cursor_prev(this);
            break;

            case 'P': case 'p':
            	if(play){
            		play=false;
            	} else{
            		play=true;
            	}
            break;

            default:
                printf("Opción inválida!\n");
            break;
        }
    } while( cmd != 'S' && cmd != 's');
}



/**
 * @brief Función de activación del segundo ménu
 *
 * @param lista Referencia al contenedor de Playlist's
 * @param lista Referencia a una playlist en particular
 * @param lista Referencia a la playlist "general"
 *
 * @pre Las listas deben existir
 * @pre Las listas deben contener al menos una canción o playlist
 */
void TestMenuPlaylist( Player* player, Playlist* this, Playlist* that)
{
    Clear();
    char optChar[MAX];
    int opt;
    char cmd;
    char str[80];

    do{
    	PrintMenuPlaylist(this);
        printf("\ncmd > > >: ");
        scanf( "%s", (char*)&str );
        cmd = str[0];

        switch( cmd )
        {
        	case 'O': case 'o':
        		if(Playlist_IsEmpty(that)){
                    printf("\n¡¡¡ %s vacío. Capture primero los datos de algunas canciones !!! \n",Playlist_GetName(that));
                    break;
                } else{

                	Playlist_MakeEmpty(this);
                	//printf("Len: %ld",Playlist_Len(this));
                	printf("\nOptimización de playlist\n");
        			printf("\nIngrase un límite de tiempo en minutos: \n");
        			printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}

        			backtracking(that,this,opt);
                }
        	break;

        	case 'C': case 'c': Clear();
			break;

        	case 'S': case 's':
			break;

            case 'H': case 'h':
			break;

            case 'A': case 'a':;  //";" corrige el error de compilación


				if( Playlist_IsEmpty(that)){
                    printf("\n¡¡¡ %s vacío. Capture primero los datos de una nueva canción !!!\n",Playlist_GetName(that));
                    break;
                } else{

					printf("\nElija una canción\n");

            		Playlist_Traverse(that,Print_TrackTitle);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(that)||opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}

                    //coloca al cursor en opt
            		Playlist_Cursor_front(that);
            		for(size_t i=0;i<opt;++i){
            			Playlist_Cursor_next(that);
            		}
            		Playlist_Cursor_prev(that);


            		Track* v1=Playlist_Get(that);
                	Playlist_Insert_back( this, v1 );
					printf("\nInsertando %s en %s...\n",Track_GetTitle(v1),Playlist_GetName(this)); //v1.title

                	//Print_DataTrack( v1 );
                }
            break;

            case 'X': case 'x':

                if( Playlist_IsEmpty( this ) == true ){
                    printf("\n¡¡¡ La playlist %s esta vacía. No hay canciones para eliminar!!!\n",Playlist_GetName(this));
                    break;
                } else{
                    printf("\nElija una canción\n");
                    Playlist_Cursor_front( this );

                    for( size_t i = 0; i<Playlist_Len( this ); ++i ){
                        printf("%ld.- ",i+1);
						puts( Track_GetTitle( Playlist_Get(this) ) ); //Aquí mostramos la lista de canciones en la playlist
                        Playlist_Cursor_next( this );
                    }

                    //size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(this)||opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}

                    Playlist_Cursor_front( this );

                    if( opt == 1){
                        printf("Removiendo ");

						puts( Track_GetTitle(Playlist_Get(this)));//Aqui
						printf("...\n");

                        Playlist_Remove_front( this );

                    } else{
                        for( size_t i = 0; i< opt-1; ++i ){
                            Playlist_Cursor_next( this );
                        }
                        printf("Removiendo ");

						puts(Track_GetTitle(Playlist_Get(this)));//Aqui//this->cursor->datos.title
                        Playlist_Remove( this );
                    }
                }
            break;

            case 'P': case 'p':

                if( Playlist_IsEmpty( this ) == true ){
                    printf("\n¡¡¡ La playlist %s esta vacía. Agregue primero una canción !!! \n",Playlist_GetName(this));
                    break;
                } else{

                	printf("\nElija una canción\n");
                	Playlist_Traverse(this,Print_TrackTitle);	//Mostramos la lista de canciones en la playlist

                    //size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(this)||opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}

                    Playlist_Cursor_front( this );

                    if( opt == 1){
                        //printf("Reproduciendo ");
						//puts( this->cursor->datos.title);
						//printf("...\n");

                    } else{

                        for( size_t i = 0; i< opt-1; ++i ){
                            Playlist_Cursor_next( this );
                        }
                    }

                    TestMenuCancion(this);		//Simulación de la reproducción

                }

            break;

            default:
                printf("Opción inválida!\n");
            break;

        }
    } while( cmd != 'S' && cmd != 's');
}



/**
 * @brief Función de activación del ménu principal
 *
 * @pre Esta función activa todo el programa y se usa en el archivo main.c
 * @post No deberian surgir memory leaks
 */
void TestPrincipal()
{
	char optChar[MAX];
	int opt;
	int id = 1;

    char cmd;
    char str[80];
    /* Se crean dos listas doblemente enlazadas la primera para guardar
       las canciones favoritas sin necesidad de estar almacenadas en una
       playlist particular de forma forzada y la segunda serviria como
       contenedor de varias playlist's
    */

	Player* player=Player_New();
	Playlist* playlist_gral=Playlist_New("Banco de canciones");


    do{
    	PrintMenuPrincipal(player,playlist_gral);
        printf("\ncmd > > >: ");
        scanf("%s", (char*)&str );
        cmd = str[ 0 ];

        switch( cmd )
        {
        	case 'X': case 'x':

        		if(Playlist_IsEmpty(playlist_gral)){
                    printf("\n¡¡¡ %s vacío. No hay canciones para eliminar !!! \n",Playlist_GetName(playlist_gral));
                    break;
                } else{

        			printf("\nElija la canción que se va a eliminar\n");
            		Playlist_Traverse(playlist_gral,Print_TrackTitle);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(playlist_gral)||opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}
                                                        //Coloca al cursor en opt
            		Playlist_Cursor_front(playlist_gral);
            		for(size_t i=0;i<opt;++i){
            			Playlist_Cursor_next(playlist_gral);
            		}
            		Playlist_Cursor_prev(playlist_gral);


            		printf("Se eliminó la canción: %s\n",Track_GetTitle(Playlist_Get(playlist_gral)));//Aqui//playlist_gral->cursor->datos.title


            		Player_GralRemove(player,Playlist_GetID(playlist_gral));	//Elimina la cancion de todas las playlists
            		Playlist_Remove(playlist_gral);								//Elimina la cancion de la lista general
            	}
        	break;


        	case 'Z': case 'z':;
        		Track *v2 = Track_New(id);

                Playlist_Insert_back( playlist_gral, v2 );
				printf("\nInsertando %s en %s...\n",Track_GetTitle(v2),Playlist_GetName(playlist_gral));

    			Track_Delete( &v2 );

    			id++;		 //Id de cada cancion

        	break;


        	case 'C': case 'c':
				Clear();
			break;

            case 'E': case 'e':
			break;


            case 'A': case 'a':

                if(Playlist_IsEmpty(playlist_gral)){
                    printf("\n¡¡¡ %s vacío. Capture primero los datos de una nueva canción !!! \n",Playlist_GetName(playlist_gral));
                    break;
                } else{

					printf("\nTodas las canciones: \n\n");
                	Playlist_Traverse(playlist_gral,Print_TrackTitle);


                }
            break;


            case 'N': case 'n':
                printf("\nNombre del Playlist: ");

                char name[MAX];

    			fgets(name,MAX,stdin);
                scanf("%[^\n]",name);

                Playlist* p1 = Playlist_New( name );

                Player_Insert_back(player,p1);
                printf("Insertando la playlist %s... \n",name);

                Playlist_Delete(&p1);


            break;

            case 'D': case 'd':
                //Funcion eliminar playlist's

                if(Player_IsEmpty(player)){
                    printf("\n¡¡¡ No hay playlists para eliminar. No se realizó ninguna acción!!!\n");
                    break;
                } else{

                	printf("\nElija una playlist\n");

            		Player_Traverse(player,Print_PlaylistName);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Player_Len(player)||opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}

            		//Coloca al cursor en opt
            		Player_Cursor_front(player);
            		for(size_t i=0;i<opt;++i){
            			Player_Cursor_next(player);
            		}
            		Player_Cursor_prev(player);
            		//////////////////////////////


            		printf("Se eliminó la playlist: %s\n",Playlist_GetName(Player_Get(player)) );//Aqui//player->cursor->datos.name
            		Player_Remove(player);
				}

            break;


            case 'R': case 'r':

            	if(Player_IsEmpty(player)){
                    printf("\n¡¡¡ Error !!! , No se han creado playlists.\n");
                    break;
                } else{

            		printf("\nElija una playlist\n");
            		Player_Traverse(player,Print_PlaylistName);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Player_Len(player)||opt<1){
            				printf("Opción inválida!\n");
            				break;
            			}
            		} else{
            			printf("Opción inválida!\n");
            			break;
            		}
            		//Coloca el cursor en la posicion opt
            		Player_Cursor_front(player);
            		for(size_t i=0;i<opt;++i){
            		Player_Cursor_next(player);
            		}
            		Player_Cursor_prev(player);


                	TestMenuPlaylist(player,Player_Get(player),playlist_gral);//Aqui//&player->cursor->datos

				}
            break;


            default:
                printf("Comando inválido\n");
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
