#include "Menus.h"
#define LIN


/**
 * @brief Limpia la pantalla
 *
 * @pre La constante LIN permite que la funci�n cumpla su proposito
 *      en Linux, definirla como WIN lo hace en Windows
 *
 * @post La pantalla debe limpiarse para mejorar el flujo de informaci�n
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
 * @brief Imprime el Men� principal
 *
 * @param lista Referencia al contenedor de listas
 * @param lista Referencia al playlist "general"
 *
 * @pre Las listas deben existir
 */

void PrintMenuPrincipal(Player* this,Playlist* that)

{
	printf("\nReproductor (%ld playlists)(%ld canciones)\n",Player_Len(this),Playlist_Len(that));

    printf("\n\tMen� principal\n");
    printf("A) Lista de canciones completa\n");    //Mostraria todas las canciones de la lista principal
    printf("N) Nueva Playlist\n");                 //Crearia una nueva playlist y la almacenaria en la lista secundaria
    printf("Z) Nueva canci�n\n");
	printf("D) Eliminar Playlist\n");              //Eliminaria una playlist contenida en la lista secundaria
    printf("X) Eliminar canci�n\n");
	printf("R) Abrir Playlist\n");                 //Mostraria un menu con opciones para una playlist
	printf("C) Limpiar pantalla\n");
	printf("E) Salir\n");                          //Salimos del programa de manera defenitiva

}



/**
 * @brief Imprime el men� de opciones de playlist
 *
 * @param lista Referencia a una playlist en particular
 *
 * @pre La lista debe existir
 */

void PrintMenuPlaylist(Playlist* this)
{

	printf("\nPlaylist: %s (%ld canciones)\n",Playlist_GetName(this),Playlist_Len(this));

    printf("\n\tMen� para Playlist\n");
    printf("A) Agregar canci�n\n");         //Agrega una canci�n a la playlist en la que se este trabajando
    printf("X) Remover canci�n\n");         //Quita una canci�n seleccionada por el usuario
	printf("P) Reproducir canci�n\n");    	//Simula la reproducci�n de la canci�n ( aun falta un detalle)
    printf("O) Optimizar Playlist\n");
    printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");                 	//Salimos de este men� y regresamos al principal
}



/**
 * @brief Imprime el men� de opciones para la canci�n
 *
 * @param lista Referencia a una playlist en particular
 * @param true si la canci�n se esta "reproduciendo"
 *        false si la canci�n esta pausada
 *
 * @pre La lista debe existir
 * @pre La lista debe contener al menos una canci�n
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

    printf("\n\tMen� para Canci�n\n");
    printf("R) Siguiente\n");
    printf("L) Anterior\n");
    printf("P) Pausar/Reproducir\n");
	printf("C) Limpiar pantalla\n");
    printf("S) Salir\n");
}



/**
 * @brief Funci�n de activaci�n del tercer m�nu
 *
 * @param lista Referencia a una playlist en particular
 *
 * @pre La lista debe existir
 * @pre La lista debe contener al menos una canci�n
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
                printf("Opci�n inv�lida!\n");
            break;
        }
    } while( cmd != 'S' && cmd != 's');
}



/**
 * @brief Funci�n de activaci�n del segundo m�nu
 *
 * @param lista Referencia al contenedor de Playlist's
 * @param lista Referencia a una playlist en particular
 * @param lista Referencia a la playlist "general"
 *
 * @pre Las listas deben existir
 * @pre Las listas deben contener al menos una canci�n o playlist
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
                    printf("\n��� %s vac�o. Capture primero los datos de algunas canciones !!! \n",Playlist_GetName(that));
                    break;
                } else{

                	Playlist_MakeEmpty(this);
                	//printf("Len: %ld",Playlist_Len(this));
                	printf("\nOptimizaci�n de playlist\n");
        			printf("\nIngrase un l�mite de tiempo en minutos: \n");
        			printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
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

            case 'A': case 'a':;  //";" corrige el error de compilaci�n


				if( Playlist_IsEmpty(that)){
                    printf("\n��� %s vac�o. Capture primero los datos de una nueva canci�n !!!\n",Playlist_GetName(that));
                    break;
                } else{

					printf("\nElija una canci�n\n");

            		Playlist_Traverse(that,Print_TrackTitle);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(that)||opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
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
                    printf("\n��� La playlist %s esta vac�a. No hay canciones para eliminar!!!\n",Playlist_GetName(this));
                    break;
                } else{
                    printf("\nElija una canci�n\n");
                    Playlist_Cursor_front( this );

                    for( size_t i = 0; i<Playlist_Len( this ); ++i ){
                        printf("%ld.- ",i+1);
						puts( Track_GetTitle( Playlist_Get(this) ) ); //Aqu� mostramos la lista de canciones en la playlist
                        Playlist_Cursor_next( this );
                    }

                    //size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(this)||opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
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
                    printf("\n��� La playlist %s esta vac�a. Agregue primero una canci�n !!! \n",Playlist_GetName(this));
                    break;
                } else{

                	printf("\nElija una canci�n\n");
                	Playlist_Traverse(this,Print_TrackTitle);	//Mostramos la lista de canciones en la playlist

                    //size_t p = 0;
                    printf("\ncmd > > >: ");
                    scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(this)||opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
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

                    TestMenuCancion(this);		//Simulaci�n de la reproducci�n

                }

            break;

            default:
                printf("Opci�n inv�lida!\n");
            break;

        }
    } while( cmd != 'S' && cmd != 's');
}



/**
 * @brief Funci�n de activaci�n del m�nu principal
 *
 * @pre Esta funci�n activa todo el programa y se usa en el archivo main.c
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
                    printf("\n��� %s vac�o. No hay canciones para eliminar !!! \n",Playlist_GetName(playlist_gral));
                    break;
                } else{

        			printf("\nElija la canci�n que se va a eliminar\n");
            		Playlist_Traverse(playlist_gral,Print_TrackTitle);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Playlist_Len(playlist_gral)||opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
            			break;
            		}
                                                        //Coloca al cursor en opt
            		Playlist_Cursor_front(playlist_gral);
            		for(size_t i=0;i<opt;++i){
            			Playlist_Cursor_next(playlist_gral);
            		}
            		Playlist_Cursor_prev(playlist_gral);


            		printf("Se elimin� la canci�n: %s\n",Track_GetTitle(Playlist_Get(playlist_gral)));//Aqui//playlist_gral->cursor->datos.title


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
                    printf("\n��� %s vac�o. Capture primero los datos de una nueva canci�n !!! \n",Playlist_GetName(playlist_gral));
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
                    printf("\n��� No hay playlists para eliminar. No se realiz� ninguna acci�n!!!\n");
                    break;
                } else{

                	printf("\nElija una playlist\n");

            		Player_Traverse(player,Print_PlaylistName);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Player_Len(player)||opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
            			break;
            		}

            		//Coloca al cursor en opt
            		Player_Cursor_front(player);
            		for(size_t i=0;i<opt;++i){
            			Player_Cursor_next(player);
            		}
            		Player_Cursor_prev(player);
            		//////////////////////////////


            		printf("Se elimin� la playlist: %s\n",Playlist_GetName(Player_Get(player)) );//Aqui//player->cursor->datos.name
            		Player_Remove(player);
				}

            break;


            case 'R': case 'r':

            	if(Player_IsEmpty(player)){
                    printf("\n��� Error !!! , No se han creado playlists.\n");
                    break;
                } else{

            		printf("\nElija una playlist\n");
            		Player_Traverse(player,Print_PlaylistName);
            		printf("\ncmd > > >: ");
            		scanf("%s",optChar);

            		if(validar(optChar)){
            			opt=atoi(optChar);
            			if(opt>Player_Len(player)||opt<1){
            				printf("Opci�n inv�lida!\n");
            				break;
            			}
            		} else{
            			printf("Opci�n inv�lida!\n");
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
                printf("Comando inv�lido\n");
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
