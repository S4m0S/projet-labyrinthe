#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <windows.h>

#include "playing.h"
//#include <ncursesw/ncurses.h>

#define true 1
#define false 0
#define tailleCase 3
#define tailleLabyrinthe 7
#define typeTuileEnT 0
#define typeTuileEnL 1
#define typeTuileEnI 2
#define nbTresor 24

typedef char* string;
typedef short int bool; 


typedef struct date
{
    int day;
    int year;
    int month;
    int hours;
    int minutes;
    int seconds;
}date;


// y sur l'axe des horizontale et x sur l'axe verticale 
typedef struct position{
    int x;
    int y;
}position;

typedef struct tresor{
    position* piece;        // addresse de la position de la pièce sur laquelle se trouve le tresor
    bool find;              // le tresor a-t-il déja eté trouvé
    char affiche;           
}tresor;

typedef struct joueur {
    position piece;
    int score;              
    char affiche;
    string nom;
    tresor listeTresor[];
}joueur;

typedef struct tuile{           // !! On doit trouver un moyen de voir où la pièce est "ouverte", c'est a dire si le joueur peut passer ou si il y a un mur 
    joueur * presenceJoueur;           // si NULL alors pas de joueurs 
    int type;
    position posActuelle;
    tresor treasure;
    bool moove;
    int orientation;                // Orientation de base : 0  chaque +1 orientation indique une rotation de 90 degrès sur la droite 
}tuile;



void printElement(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe],const char** typeTuile[3]);
bool init(int nbJoueurs,string nomJoueurs[4],char listePion[4],tuile tableauTuiles[tailleLabyrinthe][tailleLabyrinthe],joueur listeJoueurs[4],tuile * dehors);
void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe],tresor tableauTresor[nbTresor],tuile* dehors);
void affichageCase(const char fond[3][3],int k,tuile actuelle);
void initialisationJoueurs(int nbJoueurs, string nomJoueurs[4],joueur listeJoueurs[4],char listePionJoueurs[],tuile listePlateau[tailleLabyrinthe][tailleLabyrinthe]);
void initTresor(int* indexTresor,tresor* actuel,position* posPiece,tresor listeTresor[nbTresor]);
void bougerPiece(tuile* aIntegrer,position nouvellePosition,tuile listePlato[7][7],position* anciennePosition,const char** tableauTuile[3]);
//void inGame(int nbJoueurs,string nomJoueurs[nbJoueurs],char listePion[nbJoueurs]);
bool bougerJoueur(joueur *myplayer, position posActu, tuile listePlato[7][7],int direction,const char** tableau[3]);
void repartitionTresors(int nbJoueurs,joueur listeJoueurs[4], tresor listeTresor[nbTresor]);
void gotoligcol( int lig, int col );
void printTuileOut(tuile* out,const char** typeTuile[3]);


void inGame(int nbJoueurs,string nomJoueurs[4],char listePion[4]){
    tuile tableauTuiles[tailleLabyrinthe][tailleLabyrinthe];  // tableau contenant le plateau de jeu avec toutes les tuiles
    joueur* listeJoueurs = calloc(4,sizeof(joueur));                           // liste des joueurs
    bool readyToPLay = false;
    tuile* out = malloc(sizeof(tuile));
    if(init(nbJoueurs,nomJoueurs,listePion,tableauTuiles,listeJoueurs,out))
        readyToPLay = true;
    else
        return;
    const char typeT[tailleCase][tailleCase] = {{'#','#','#'},{' ',' ',' '},{'#',' ','#'}}; // type 0 : representation des pièces
    const char typeL[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ',' '},{'#','#','#'}}; // type 1 : sur le plateau grace a cela
    const char typeI[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ','#'},{'#',' ','#'}}; // type 2 : on peut les affichers
    const char** typeTpointer = typeT;
    const char** typeLpointer = typeL;
    const char** typeIpointer = typeI;
    const char** typeTuile[3] = {typeTpointer, typeLpointer, typeIpointer}; // liste contenant toutes les addresses des representations des pièces 
    bool play = true;
    printf("%c\n",tableauTuiles[0][0].presenceJoueur->affiche);
    while(getchar()!='\n');
    system("cls");
    printElement(tableauTuiles,typeTuile);
    while(getchar()!='\n');
    int tourDe = 0;
    char input;
    while(play)
    {
        printElement(tableauTuiles,typeTuile);
        printf("C'est le tour de %s" ,nomJoueurs[tourDe]);
        while(getchar()!='\n');
        printf("Bouger une pièce sur le terain !");
        /*
        do{
            input = getchar();
            if(input == 37)//left

            else if(intput == 38)// top

            else if(input == 39) // right

            else if(input==40)  //bottom
            printElement(tableauTuiles,typeTuile);
            
        }
        while(getchar()!='\n');*/
        printf("Bouger votre pion");
        do{
            input = getchar();
            if(input=='z')
                bougerJoueur(&listeJoueurs[tourDe],listeJoueurs[tourDe].piece,tableauTuiles,0,typeTuile);
            else if(input=='d')
                bougerJoueur(&listeJoueurs[tourDe],listeJoueurs[tourDe].piece,tableauTuiles,1,typeTuile);
            else if(input=='s')
                bougerJoueur(&listeJoueurs[tourDe],listeJoueurs[tourDe].piece,tableauTuiles,2,typeTuile);
            else if(input=='q')
                bougerJoueur(&listeJoueurs[tourDe],listeJoueurs[tourDe].piece,tableauTuiles,3,typeTuile);
        }while(getchar()!='n');
        tourDe++;
        tourDe = tourDe%4;
        //fonction pour check si un joueur a gagner;
        system("cls");
    }
}




void myloop(int nbJoueur,char listePion[4],string nomJoueur[4])
{
    const char typeT[tailleCase][tailleCase] = {{'#','#','#'},{' ',' ',' '},{'#',' ','#'}}; // type 0 : representation des pièces
    const char typeL[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ',' '},{'#','#','#'}}; // type 1 : sur le plateau grace a cela
    const char typeI[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ','#'},{'#',' ','#'}}; // type 2 : on peut les affichers
    const char** typeTpointer = typeT;
    const char** typeLpointer = typeL;
    const char** typeIpointer = typeI;
    const char** typeTuile[3] = {typeTpointer, typeLpointer, typeIpointer}; // liste contenant toutes les addresses des representations des pièces 
    tuile tableauTuiles[tailleLabyrinthe][tailleLabyrinthe];
    char (*listeNom)[4] = {"Adam","MIKE","JUGE","JEAN"};
    joueur *listeJoueur = calloc(4,sizeof(joueur));
    tuile* out = malloc(sizeof(tuile));
    //init(nbJoueur,listeNom,listePion,tableauTuiles,listeJoueur,out);
    srand(time(NULL));
    tresor tableauTresor[nbTresor];
    initialisationTuiles(tableauTuiles,tableauTresor,out);
    initialisationJoueurs(nbJoueur,listeNom,listeJoueur,listePion,tableauTuiles);
    repartitionTresors(nbJoueur,listeJoueur,tableauTresor);
    out->posActuelle.x = -1;
    out->posActuelle.y = 1;
    system("cls");
    printElement(tableauTuiles,typeTuile);
    //printTuileOut(out,typeTuile);
    char input;
    bool pasDeplacer = true;
    position derniere = {0,0};
    int indexPlaying = 0;
    bool playing = true;
    printf("\nPour vous dirigez utiliser les les touches z/q/s/d, pour tourner une pièce essayer la touche r.\n Enfin pour sortir du jeu c'est la touche a. Pour valider une case se sera g. \n On est parti ? ");
    while(getchar()!='\n');
    system("cls");
    printElement(tableauTuiles,typeTuile);
    
    while(playing){
    do{
        printf("Choisisez un endroit oû bouger la piece : ");
        scanf("%c",&input);
        while(getchar()!='\n');
        if(input =='z')
        {
            //bouger la pièce dehors 
            if(((out->posActuelle.x==-1 || out->posActuelle.x==7) && (out->posActuelle.y!=1||out->posActuelle.y!=5)))  // pas sur du 5
                printf("mouvement impossible \n");
            else if(out->posActuelle.x<5 && out->posActuelle.x>=1)
                out->posActuelle.x+=2;
            else if(out->posActuelle.x==1 && (out->posActuelle.y == -1 || out->posActuelle.y == 7)){
                out->posActuelle.x=-1;
                out->posActuelle.y = out->posActuelle.y=7 ? 5:1;
            }
        }
        else if(input=='s')
        {
            if(((out->posActuelle.x==-1 || out->posActuelle.x==7) && (out->posActuelle.y!=1||out->posActuelle.y!=5)))   // pas sur du 5 la non plus
                printf("mouvement impossible \n");
            else if(out->posActuelle.x>=5 && out->posActuelle.x>1)
                out->posActuelle.x-=2;
            else if(out->posActuelle.x==5 && (out->posActuelle.y == -1 || out->posActuelle.y == 7)){
                out->posActuelle.x=7;
                out->posActuelle.y = out->posActuelle.y=7 ? 5:1;
            }
            //same
        }
        else if(input=='d')
        {
            if(((out->posActuelle.y==-1 || out->posActuelle.y==7) && (out->posActuelle.x!=1||out->posActuelle.x!=5)))   // pas sur du 5 la non plus
                printf("mouvement impossible \n");
            else if(out->posActuelle.y<5 && out->posActuelle.y>=1)
                out->posActuelle.y-=2;
            else if(out->posActuelle.y==5 && (out->posActuelle.x == -1 || out->posActuelle.x == 7)){        // pas fini encore cette partie
                out->posActuelle.y=7;
                out->posActuelle.x = out->posActuelle.x=7 ? 5:1;
            }
            //same 
        }
        else if(input=='q')
        {
            if(((out->posActuelle.y==-1 || out->posActuelle.y==7) && (out->posActuelle.x!=1||out->posActuelle.x!=5)))   // pas sur du 5 la non plus
                printf("mouvement impossible \n");
            else if(out->posActuelle.y<=5 && out->posActuelle.y>1)
                out->posActuelle.y+=2;
            else if(out->posActuelle.x==1 && (out->posActuelle.y == -1 || out->posActuelle.y == 7)){    // ca non plus
                out->posActuelle.y=7;
                out->posActuelle.x = out->posActuelle.x=7 ? 5:1;
            }
            //same 
        }
        else if(input=='r')
        {
            out->orientation++;
            out->orientation=out->orientation%4;
        }
        else if(input=='g')
        {
            position nouvellePosition = out->posActuelle;
            if(nouvellePosition.x == derniere.x-6 || nouvellePosition.x == derniere.x+6 || nouvellePosition.y == derniere.y-6 || nouvellePosition.y == derniere.y+6)
                pasDeplacer=true;
            else
                pasDeplacer=false;
        }
        else if(input=='a');
            playing =false;
    }while(input!='g' && pasDeplacer);
    bougerPiece(out,out->posActuelle,tableauTuiles,&derniere,typeTuile);
    input = 'm';
    do{
        printf("position joueur : x  :  %i  ;   y   :   %i\n",listeJoueur[indexPlaying].piece.x,listeJoueur[indexPlaying].piece.y);
        printf("Voici les prochains trésor que vous devrez trouver : ");
        for(int l = 0;l<nbTresor/nbJoueur;l++)
        {
            if(listeJoueur[indexPlaying].listeTresor[l].find==false)
                printf("%c ;",listeJoueur[indexPlaying].listeTresor[l].affiche);
        }
        printf("\nChoisisez où bouger : ");
        scanf("%c",&input);
        while(getchar()!='\n');
        if(input=='z')
            bougerJoueur(&listeJoueur[indexPlaying],listeJoueur[indexPlaying].piece,tableauTuiles,0,typeTuile);
        else if(input=='d')
            bougerJoueur(&listeJoueur[indexPlaying],listeJoueur[indexPlaying].piece,tableauTuiles,1,typeTuile);
        else if(input=='s')
            bougerJoueur(&listeJoueur[indexPlaying],listeJoueur[indexPlaying].piece,tableauTuiles,2,typeTuile);
        else if(input=='q')
            bougerJoueur(&listeJoueur[indexPlaying],listeJoueur[indexPlaying].piece,tableauTuiles,3,typeTuile);
        
        if(input=='a');
            playing =false;
    }while(input!='g');
    checkWinner(&listeJoueur[indexPlaying],nbJoueur);
    if(listeJoueur[indexPlaying].score==nbTresor){
        printf("Bravo, le joueur a gagner");
        while(getchar()!='\n');
        playing = false;
    }
    indexPlaying++;
    indexPlaying = indexPlaying%nbJoueur;
}

}



void checkWinner(joueur *player,int nbJoueur)
{
    for(int i = 0;i<nbTresor/nbJoueur;i++)
    {
        if(player->piece.x==player->listeTresor[i].piece->x && player->piece.y==player->listeTresor[i].piece->y)
        {
            player->score++;
            player->listeTresor[i].find = true;
        }
    }
}

/*
void gotoligcol( int lig, int col ) {

// ressources

    COORD mycoord;

    mycoord.X = col;

    mycoord.Y = lig;

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );

}

void printTuileOut(tuile* out,const char** typeTuile[3])

{
    for(int i = 0; i < tailleCase; i++)
    {
        //gotoligcol(out->posActuelle.x*3,out->posActuelle.y*3+i);
        gotoligcol(0,i);
        if(out->type == typeTuileEnT)
            affichageCase(typeTuile[0],i,*out);
        else if(out->type == typeTuileEnL)
            affichageCase(typeTuile[1],i,*out);
        else
            affichageCase(typeTuile[2],i,*out);
        printf("\n");
    }
}
*/
bool init(int nbJoueurs,string nomJoueurs[4],char listePion[4],tuile tableauTuiles[tailleLabyrinthe][tailleLabyrinthe],joueur listeJoueurs[4],tuile * dehors)         // fonction d'initialisation du jeu une fois celle-ci effectuer on peut commencer a jouer 
{                       // elle permet d'initialiser toutes les tuiles, de gerer le nombre de joueurs, la distrubution des cartes trésor...
    srand(time(NULL));
    tresor tableauTresor[nbTresor];
    initialisationTuiles(tableauTuiles,tableauTresor,dehors);
    
    // creation des joueurs 
    
    initialisationJoueurs(nbJoueurs,nomJoueurs,listeJoueurs,listePion,tableauTuiles);
    //printElement(tableauTuiles,typeTuile);
    repartitionTresors(nbJoueurs,listeJoueurs,tableauTresor);
    // afficher les elements 
    return true;
}


//  fonction de test 
void printElement(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe],const char** typeTuile[3])
{   
    printf("\n\n\n\n");
    for(int i = 0 ; i<tailleLabyrinthe;i++)
    {
        for(int k =0;k<tailleCase;k++)
        {
            printf("     ");
            for(int j = 0;j<tailleLabyrinthe;j++)
            {
                // gerer l'orientation ici 
                // suite dans la fonction affichage case 
                if(tableauTuile[i][j].type == typeTuileEnT)
                    affichageCase(typeTuile[0],k,tableauTuile[i][j]);
                else if(tableauTuile[i][j].type == typeTuileEnL)
                    affichageCase(typeTuile[1],k,tableauTuile[i][j]);
                else
                    affichageCase(typeTuile[2],k,tableauTuile[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}

void affichageCase(const char fond[3][3],int k,tuile actuelle)
{
    // Verifier l'affichage en fonction de l'orientation because c'est bizzare la actuellement
    switch (actuelle.orientation)
    {
        case 0:
            for(int j = 0;j<tailleCase;j++)
            {
            if(k==1 && j==1 && actuelle.treasure.piece!= NULL && actuelle.treasure.find == false)  // tresor probleme d'affichage 
                printf("%c",actuelle.treasure.affiche);             
            else if(k==1 && j==1 && actuelle.presenceJoueur != NULL)    // ou les personnage
                printf("%c",actuelle.presenceJoueur->affiche);
            else if(fond[k][j]==' ')
                printf(" ");
            else
                printf("%c",fond[k][j]);
            }
            break;
        case 1:
            for(int j = 0;j<tailleCase;j++)
            {
            if(k==1 && j==1 && actuelle.treasure.piece!= NULL && actuelle.treasure.find == false)
                printf("%c",actuelle.treasure.affiche);
            else if(k==1 && j==1 && actuelle.presenceJoueur != NULL)
                printf("%c",actuelle.presenceJoueur->affiche);
            else if(fond[2-j][k]==' ')
                printf(" ");
            else
                printf("%c",fond[2-j][k]);
            }
            break;
        case 2:
            for(int j = 0;j<tailleCase;j++)
            {
            if(k==1 && j==1 && actuelle.treasure.piece!= NULL && actuelle.treasure.find == false)
                printf("%c",actuelle.treasure.affiche);
            else if(k==1 && j==1 && actuelle.presenceJoueur != NULL)
                printf("%c",actuelle.presenceJoueur->affiche);
            else if(fond[2-k][2-j]==' ')
                printf(" ");
            else
                printf("%c",fond[2-k][2-j]);
            }
            break;
        case 3:
            for(int j = 0;j<tailleCase;j++)
            {
            if(k==1 && j==1 && actuelle.treasure.piece!= NULL && actuelle.treasure.find == false)
                printf("%c",actuelle.treasure.affiche);
            else if(k==1 && j==1 && actuelle.presenceJoueur != NULL)
                printf("%c",actuelle.presenceJoueur->affiche);
            else if(fond[j][2-k]==' ')
                printf(" ");
            else
                printf("%c",fond[j][2-k]);
            }
            break;
    }
    printf("  ");
}




void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe],tresor tableauTresor[nbTresor],tuile* dehors)
{   // cette fonction permet d'initialiser les tuiles du tableau aléatoirement 
    // elle s'occupe de la mise en place des tuiles dans le tableau passer en parrametre

    int tuileTnombreAvecTresor = 6;     // ICI type 0 pour check l'aleatoire  : Ces vairiables servent à compter le nombre de
    int tuileLnombreAvecTresor = 6;     // ICI type 1 pour check l'aleatoire  : pièces disponibles lors de l'attribution 
    int tuileLnombre = 10;              // ICI type 2 pour check l'aleatoire  : aléatoire de celle-ci
    int tuileInombre = 12;              // ICI type 3 pour check l'aleatoire
    int typeTuileAleatoire;             // Vairable pour faire un choix entre les 4 variables ci-dessus
    bool possible;                      // check si la pièce aleatoire est bien disponible 
    int checkValue[4] = {0,2,4,6};      // valeur pour lesquels le tes pièces seront immobiles
    bool checkImmobile;                 // si true la piece est immobile 
    int indexTresor = 0;                // index de la representation des tresor
    for(int i = 0;i<tailleLabyrinthe;i++)
    {
        for(int j = 0;j<tailleLabyrinthe;j++)
        {
            
            tuile actuel;           // initialisationd de la tuile actuelle, celle-ci sera ensuite inserer dans le tableau
            actuel.presenceJoueur = NULL;
            checkImmobile = false;
            position posActuel;
            posActuel.x = i;
            posActuel.y = j;
            actuel.posActuelle = posActuel;
            {
                tresor pasDeTresor;
                pasDeTresor.piece = NULL;
                actuel.treasure = pasDeTresor;
            }
            for(int p = 0;p<4;p++)
            {
                for(int m = 0;m<4;m++)
                {
                    if(checkValue[p]==i && checkValue[m]==j)
                        checkImmobile=true;
                }
            }
            if(checkImmobile==true)    // on regarde si la pièce est une pièce qui ne peut pas bouger
            {
                // le test ci dessus est peut etre pas bon en fait
                actuel.moove = false;
                actuel.orientation = 0;         // si c'est le cas, on l'initialise comme tel 
                switch (i)
                {
                    case 0:
                        switch (j)
                        {
                        case 0:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 1;
                            // pas de tresor mais depart d'un joueur ici 
                            break;
                        case 2 :
                        case 4 :
                            actuel.type = typeTuileEnT;
                            actuel.orientation = 0;
                            tresor nouveau;
                            initTresor(&indexTresor,&nouveau,&actuel.posActuelle,tableauTresor);
                            actuel.treasure = nouveau;
                            break; 
                        case 6:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 2;
                            // depart de joueurs
                            break;
                        }
                        break;
                    case 2 :
                        actuel.type = typeTuileEnT;
                        switch (j)
                        {
                        case 0:
                        case 2:
                            actuel.orientation = 3;
                            break;
                        case 4:
                            actuel.orientation = 0;
                            break;
                        case 6:
                            actuel.orientation = 1;
                            break;
                        }
                        tresor nouveau;
                        initTresor(&indexTresor,&nouveau,&actuel.posActuelle,tableauTresor);
                        actuel.treasure = nouveau;
                        break;
                    case 4 :
                        actuel.type = typeTuileEnT;
                        switch (j)
                        {
                        case 0:
                            actuel.orientation = 3;
                            break;
                        case 2:
                            actuel.orientation = 2;
                            break;
                        case 4:
                            actuel.orientation = 1;
                            break;
                        case 6:
                            actuel.orientation = 1;
                            break;
                        }
                        //tresor nouveau;
                        initTresor(&indexTresor,&nouveau,&actuel.posActuelle,tableauTresor);
                        actuel.treasure = nouveau;
                        break;
                    case 6 : 
                        switch (j)
                        {       
                        case 0:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 0;
                            //depart joueurs
                            break;
                        case 2:
                        case 4: 
                            actuel.type = typeTuileEnT;
                            actuel.orientation = 2;
                            tresor nouveau;
                            initTresor(&indexTresor,&nouveau,&actuel.posActuelle,tableauTresor);
                            actuel.treasure = nouveau;
                            break;
                        case 6:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 3;
                            //depart joueurs
                            break;
                        }
                        break;
                }
                
            }
            else
            {                               // si ce n'esy pas le cas, on prend une pièce aléatoire dispo dans un sens aléatoire
                actuel.moove = true;
                actuel.orientation = rand() % 4;
                // donner un type a chaque tuile en aleatoirement mais en faisant attetion que ce type de tuile est tjs dispo
                do{
                    possible = false;
                    typeTuileAleatoire = rand() % 4;
                    switch (typeTuileAleatoire) // check de si la pièce aleatoire est dipso
                    {
                    case 0:
                        if(tuileTnombreAvecTresor != 0)
                        {
                            possible = true;
                            actuel.type = typeTuileEnT;
                            tresor nouveau;
                            initTresor(&indexTresor,&nouveau,&actuel.posActuelle,tableauTresor);
                            actuel.treasure = nouveau;
                            tuileTnombreAvecTresor--;
                        }
                        break;
                    case 1:
                        if(tuileLnombreAvecTresor!=0)
                        {
                            possible =true;
                            actuel.type = typeTuileEnL;
                            tresor nouveau;
                            initTresor(&indexTresor,&nouveau,&actuel.posActuelle,tableauTresor);
                            actuel.treasure = nouveau;
                            tuileLnombreAvecTresor--;
                            // tresor !!
                        }
                        break;
                    case 2:
                        if(tuileLnombre != 0)
                        {
                            possible = true;
                            actuel.type = typeTuileEnL;
                            tuileLnombre--;
                        }
                        break;
                    case 3:
                        if(tuileInombre!=0)
                        {
                            possible = true;
                            actuel.type = typeTuileEnI;
                            tuileInombre--;
                        }
                        break;
                    }
                }while(possible!=true);
                
            }
            
            tableauTuile[i][j] = actuel;
            
        }
    }
    dehors->moove = true;
    dehors->orientation = rand() %4;
    dehors->posActuelle.x = -1;
    dehors->posActuelle.y = -1;
    dehors->presenceJoueur = NULL;
    if(tuileLnombreAvecTresor>0 || tuileTnombreAvecTresor >0)
    {
        tresor nouveau;
        initTresor(&indexTresor,&nouveau,&dehors->posActuelle,tableauTresor);
        dehors->treasure = nouveau;
        dehors->type = tuileLnombreAvecTresor=1 ? typeTuileEnL:typeTuileEnT;
    }
    else{
        tresor nouveau;
        nouveau.piece = NULL;
        dehors->treasure = nouveau;
        dehors->type = tuileInombre=1 ? typeTuileEnI:typeTuileEnL;
    }
    printf("peut-elle bouger ? %i\n",dehors->moove);
    while(getchar()!='\n');

}   

void initialisationJoueurs(int nbJoueurs, string nomJoueurs[4],joueur listeJoueurs[4],char listePionJoueurs[],tuile listePlateau[tailleLabyrinthe][tailleLabyrinthe]){
    //char listeRepresentation[4] = {'♥','♦','♣','♠'};
    char listeRepresentation[4] = {'w','x','c','v'};
    int listePosition[4][2]= {{0,0},{0,6},{6,0},{6,6}};
    joueur *listePointerJoueurs = calloc(4,sizeof(joueur)); // !!!!!! free ca faire un max de valgrind pour bien check 0 leaks
    for(int i = 0;i<nbJoueurs;i++)
    {
        joueur* actuel = &listePointerJoueurs[i];
        actuel->nom = nomJoueurs[i];
        actuel->affiche = listeRepresentation[i];
        actuel->score = 0;
        position joueurActuel;
        joueurActuel.x = listePosition[i][0];
        joueurActuel.y = listePosition[i][1];
        actuel->piece = joueurActuel;
        listePlateau[listePosition[i][0]][listePosition[i][1]].presenceJoueur = actuel;
    }
}

void initTresor(int* indexTresor,tresor* actuel,position* posPiece,tresor listeTresor[nbTresor])
{
    char listeRepresentation[nbTresor] = {'1','2','3','4','5','6','7','8','9','0','A','Z','E','R','T','Y','U','I','O','P','Q','S','D','F'};
    actuel->affiche = listeRepresentation[*indexTresor];
    actuel->find = false;
    actuel->piece = posPiece;
    listeTresor[*indexTresor] = *actuel;
    *indexTresor+=1;
}


void repartitionTresors(int nbJoueurs,joueur listeJoueurs[4], tresor listeTresor[nbTresor]){//jespere ca marche ca
    int tableauIndex[24]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    for (int i=0;i<24/nbJoueurs;i++){
        for(int j=0;j<nbJoueurs;j++){
            int random=0;
            do{
            random=rand()%24;}
            while(tableauIndex[random]==100);
            listeJoueurs[j].listeTresor[i]=listeTresor[random];    // cet ligne bug et je comprend pas ce que veut dire le listeTresor.list...
            tableauIndex[random]=100;                            // apres reflexion tu me vois dans le regret de t'annoncer que ca marche pas 
        }
    }
}

/*
void impressionJoueur(tuile presente)
{
    return;
}

int deplacement(tuile *integrer,position oumettre,tuile listePlato[7][7])
{
    return;
}
*/
void bougerPiece(tuile* aIntegrer,position nouvellePosition,tuile listePlato[7][7],position* anciennePosition,const char** tableauTuile[3])
{
    
    *anciennePosition = nouvellePosition;
    tuile* quiSaute = nouvellePosition.x==0 ? &listePlato[6][nouvellePosition.y]:(nouvellePosition.x==6 ? &listePlato[0][nouvellePosition.y]:(nouvellePosition.y==0 ? &listePlato[nouvellePosition.x][6]:&listePlato[nouvellePosition.x][0]));// test pour savoir quelle est la tuille qui saute
    int i = quiSaute->posActuelle.x==0 ? 0:(quiSaute->posActuelle.x==6 ? 6:quiSaute->posActuelle.x); 
    for(i = 0; i < tailleLabyrinthe;i++)
    {

    }
    system("cls");
    printElement(listePlato,tableauTuile);
}


/*bool bougerJoueur(joueur Joueur, position posActu, tuile listePlato[7][7],int direction,const char** tableau[3]){
    tuile nextCase;
    if(direction==0&&posActu.x-1>=0){
            nextCase= listePlato[posActu.x-1][posActu.y];
            if ((nextCase.orientation==0&&nextCase.type==0)||(nextCase.orientation==1&&nextCase.type==0)||(nextCase.orientation==2&&nextCase.type==0)||(nextCase.orientation==1&&nextCase.type==1)||(nextCase.orientation==2&&nextCase.type==1)||(nextCase.orientation==2&&nextCase.type==2)||(nextCase.orientation==2&&nextCase.type==2)){
                Joueur.piece.x=nextCase.posActuelle.x;}
            system("cls");
            printElement(listePlato,tableau);
            return true;
    }
    else if(direction==2&&posActu.x+1<=6){
            nextCase= listePlato[posActu.x+1][posActu.y];
            if ((nextCase.orientation==0&&nextCase.type==1)||(nextCase.orientation==3&&nextCase.type==1)||(nextCase.orientation==2&&nextCase.type==2)||(nextCase.orientation==0&&nextCase.type==2)||(nextCase.orientation==1&&nextCase.type==0)||(nextCase.orientation==2&&nextCase.type==0)||(nextCase.orientation==3&&nextCase.type==0)){
                Joueur.piece.x=nextCase.posActuelle.x;}
            system("cls");
            printElement(listePlato,tableau);
            return  true;
    }
    else if(direction==1&&posActu.y+1<=6){
            nextCase= listePlato[posActu.x][posActu.y+1];
            if ((nextCase.orientation==0&&nextCase.type==0)||(nextCase.orientation==1&&nextCase.type==1)||(nextCase.orientation==1&&nextCase.type==1)||(nextCase.orientation==2&&nextCase.type==1)||(nextCase.orientation==1&&nextCase.type==2)||(nextCase.orientation==3&&nextCase.type==2)){
                Joueur.piece.y=nextCase.posActuelle.y;}
            system("cls");
            printElement(listePlato,tableau);
            return true;
    }
    else if(direction==3&&posActu.y-1>=0){
            nextCase= listePlato[posActu.x][posActu.y-1];
            if ((nextCase.orientation==0&&nextCase.type==0)||(nextCase.orientation==2&&nextCase.type==0)||(nextCase.orientation==3&&nextCase.type==0)||(nextCase.orientation==0&&nextCase.type==1)||(nextCase.orientation==1&&nextCase.type==1)||(nextCase.orientation==1&&nextCase.type==2)||(nextCase.orientation==3&&nextCase.type==2)){
                Joueur.piece.y=nextCase.posActuelle.y;}
            system("cls");
            printElement(listePlato,tableau);
            return true;}
    else{
        return false;
    }
}
*/
bool bougerJoueur(joueur *myplayer, position posActu, tuile listePlato[7][7],int direction,const char** tableau[3])
{
    tuile caseSuivante;
    tuile caseActuel = listePlato[posActu.x][posActu.y];
    if(direction==0 && posActu.x!=0)
    {
        caseSuivante = listePlato[posActu.x-1][posActu.y];
        if((caseSuivante.type==typeTuileEnI && (caseSuivante.orientation==0||caseSuivante.orientation==2))||(caseSuivante.type==typeTuileEnL && (caseSuivante.orientation==1 || caseSuivante.orientation==2))||(caseSuivante.type==typeTuileEnT && (caseSuivante.orientation!=2)))
        {
            if((caseActuel.type==typeTuileEnI && (caseActuel.orientation==0||caseActuel.orientation==2))||(caseActuel.type==typeTuileEnL && (caseActuel.orientation==0 || caseActuel.orientation==3))||(caseActuel.type==typeTuileEnT && (caseActuel.orientation!=0)))
            {
                myplayer->piece.x--;
                
                listePlato[posActu.x--][posActu.y].presenceJoueur = myplayer;
                listePlato[posActu.x][posActu.y].presenceJoueur = NULL;
            }
        }   
    }
    else if(direction==2 && posActu.x!=6)
    {
        caseSuivante = listePlato[posActu.x+1][posActu.y];
        if((caseSuivante.type==typeTuileEnI && (caseSuivante.orientation==0||caseSuivante.orientation==2))||(caseSuivante.type==typeTuileEnL && (caseSuivante.orientation==0 || caseSuivante.orientation==3))||(caseSuivante.type==typeTuileEnT && (caseSuivante.orientation!=0)))
        {
            if((caseActuel.type==typeTuileEnI && (caseActuel.orientation==0||caseActuel.orientation==2))||(caseActuel.type==typeTuileEnL && (caseActuel.orientation==1 || caseActuel.orientation==2))||(caseActuel.type==typeTuileEnT && (caseActuel.orientation!=2)))
            {
                myplayer->piece.x++;
                listePlato[posActu.x++][posActu.y].presenceJoueur = myplayer;
                listePlato[posActu.x][posActu.y].presenceJoueur = NULL;
                
            }
        }   
    }
    else if(direction==1 && posActu.y!=6)
    {
        caseSuivante = listePlato[posActu.x][posActu.y+1];
        if((caseSuivante.type==typeTuileEnI && (caseSuivante.orientation==1||caseSuivante.orientation==3))||(caseSuivante.type==typeTuileEnL && (caseSuivante.orientation==2 || caseSuivante.orientation==3))||(caseSuivante.type==typeTuileEnT && (caseSuivante.orientation!=3)))
        {
            if((caseActuel.type==typeTuileEnI && (caseActuel.orientation==1||caseActuel.orientation==3))||(caseActuel.type==typeTuileEnL && (caseActuel.orientation==1 || caseActuel.orientation==0))||(caseActuel.type==typeTuileEnT && (caseActuel.orientation!=1)))
            {
                if(myplayer==NULL)
                    printf("PTNN");
                while(getchar()!='\n');
                myplayer->piece.y++;
                listePlato[posActu.x][posActu.y++].presenceJoueur = myplayer;
                listePlato[posActu.x][posActu.y].presenceJoueur = NULL;
            }
        }   
    }
    else if(direction==3 && posActu.y!=0)
    {
        caseSuivante = listePlato[posActu.x][posActu.y-1];
        if((caseSuivante.type==typeTuileEnI && (caseSuivante.orientation==1||caseSuivante.orientation==3))||(caseSuivante.type==typeTuileEnL && (caseSuivante.orientation==1 || caseSuivante.orientation==0))||(caseSuivante.type==typeTuileEnT && (caseSuivante.orientation!=1)))
        {
            if((caseActuel.type==typeTuileEnI && (caseActuel.orientation==1||caseActuel.orientation==3))||(caseActuel.type==typeTuileEnL && (caseActuel.orientation==2 || caseActuel.orientation==3))||(caseActuel.type==typeTuileEnT && (caseActuel.orientation!=3)))
            {
                myplayer->piece.y--;
                listePlato[posActu.x][posActu.y--].presenceJoueur = myplayer;
                listePlato[posActu.x][posActu.y].presenceJoueur = NULL;
                
            }
        }   
    }
    system("cls");
    printElement(listePlato,tableau);
    return true;

}
