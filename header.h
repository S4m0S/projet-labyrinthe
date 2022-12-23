#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "playing.h"

#define true 1
#define false 0
#define tailleCase 3
#define tailleLabyrinthe 7
#define typeTuileEnT 500
#define typeTuileEnL 501
#define typeTuileEnI 502
#define nbTresor 24

typedef char* string;
typedef short int bool; 


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
    int type;
    position posActuelle;
    tresor treasure;
    bool moove;
    int orientation;                // Orientation de base : 0  chaque +1 orientation indique une rotation de 90 degrès sur la droite 
}tuile;


void printElement(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe],const char** typeTuile[3]);
bool init(int nbJoueurs,string nomJoueurs[nbJoueurs]);
void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe]);
void affichageCase(const char fond[3][3],int k,int orientation);
void initialisationJouers(int nbJoueurs, string nomJoueurs[nbJoueurs],joueur listeJoueurs[nbJoueurs]);
void initTresor(int* indexTresor,tresor actuel,position* posPiece);



bool init(int nbJoueurs,string nomJoueurs[nbJoueurs])         // fonction d'initialisation du jeu une fois celle-ci effectuer on peut commencer a jouer 
{                       // elle permet d'initialiser toutes les tuiles, de gerer le nombre de joueurs, la distrubution des cartes trésor...
    srand(time(NULL));
    const char typeT[tailleCase][tailleCase] = {{'#','#','#'},{' ',' ',' '},{'#',' ','#'}}; // type 0 : representation des pièces
    const char typeL[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ',' '},{'#','#','#'}}; // type 1 : sur le plateau grace a cela
    const char typeI[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ','#'},{'#',' ','#'}}; // type 2 : on peut les affichers
    const char** typeTpointer = typeT;
    const char** typeLpointer = typeL;
    const char** typeIpointer = typeI;
    const char** typeTuile[3] = {typeTpointer, typeLpointer, typeIpointer}; // liste contenant toutes les addresses des representations des pièces 
    tuile tableauTuiles[tailleLabyrinthe][tailleLabyrinthe]; // tableau contenant le plateau de jeu avec toutes les tuiles
    initialisationTuiles(tableauTuiles);
    printElement(tableauTuiles,typeTuile);
    // creation des joueurs 
    joueur listeJoueurs[nbJoueurs];
    initialisationJouers(nbJoueurs,nomJoueurs,listeJoueurs);
    // afficher les elements 
    return true;
}


//  fonction de test 
void printElement(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe],const char** typeTuile[3])
{   
    for(int i = 0 ; i<tailleLabyrinthe;i++)
    {
        for(int k =0;k<tailleCase;k++)
        {
            for(int j = 0;j<tailleLabyrinthe;j++)
            {
                // gerer l'orientation ici 
                // suite dans la fonction affichage case 
                if(tableauTuile[i][j].type == typeTuileEnT)
                    affichageCase(typeTuile[0],k,tableauTuile[i][j].orientation);
                else if(tableauTuile[i][j].type == typeTuileEnL)
                    affichageCase(typeTuile[1],k,tableauTuile[i][j].orientation);
                else
                    affichageCase(typeTuile[2],k,tableauTuile[i][j].orientation);
            }
            printf("\n");
        }
        printf("\n\n");
    }
}

void affichageCase(const char fond[3][3],int k,int orientation)
{
    // Verifier l'affichage en fonction de l'orientation because c'est bizzare la actuellement
    switch (orientation)
    {
        case 0:
            for(int j = 0;j<tailleCase;j++)
            {
            if(fond[k][j]==' ')
                printf(" ");
            else
                printf("%c",fond[k][j]);
            }
            break;
        case 1:
            for(int j = 0;j<tailleCase;j++)
            {
            if(fond[2-j][k]==' ')
                printf(" ");
            else
                printf("%c",fond[2-j][k]);
            }
            break;
        case 2:
            for(int j = 0;j<tailleCase;j++)
            {
            if(fond[2-k][2-j]==' ')
                printf(" ");
            else
                printf("%c",fond[2-k][2-j]);
            }
            break;
        case 3:
            for(int j = 0;j<tailleCase;j++)
            {
            if(fond[j][2-k]==' ')
                printf(" ");
            else
                printf("%c",fond[j][2-k]);
            }
            break;
    }
    printf("  ");
}




void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe])
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
            checkImmobile = false;
            position posActuel;
            posActuel.x = i;
            posActuel.y = j;
            actuel.posActuelle = posActuel;
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
                            initTresor(&indexTresor,nouveau,&actuel.posActuelle);
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
                        initTresor(&indexTresor,nouveau,&actuel.posActuelle);
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
                        initTresor(&indexTresor,nouveau,&actuel.posActuelle);
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
                            initTresor(&indexTresor,nouveau,&actuel.posActuelle);
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
                            initTresor(&indexTresor,nouveau,&actuel.posActuelle);
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
                            initTresor(&indexTresor,nouveau,&actuel.posActuelle);
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
}

void initialisationJouers(int nbJoueurs, string nomJoueurs[nbJoueurs],joueur listeJoueurs[nbJoueurs],char listePionJoueurs[]){
    char listeRepresentation[4] = {'♥','♦','♣','♠'};
    int listePosition[4][2]= {{0,0},{0,6},{6,0},{6,6}};
    for(int i = 0;i<nbJoueurs;i++)
    {
        joueur actuel;
        actuel.nom = nomJoueurs[i];
        actuel.affiche = listePionJoueurs[i];
        actuel.score = 0;
        position joueurActuel;
        joueurActuel.x = listePosition[i][0];
        joueurActuel.y = listePosition[i][1];
        actuel.piece = joueurActuel;
    }
}

void initTresor(int* indexTresor,tresor actuel,position* posPiece)
{
    char listeRepresentation[nbTresor] = {'*','^','$','£','¤','µ','%','ù','¨','!','§',':','/','.',';','?',',','+','=','@','ç'};
    actuel.affiche = listeRepresentation[*indexTresor];
    actuel.find = false;
    actuel.piece = posPiece;
    *indexTresor++;
}



