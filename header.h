#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define tailleCase 3
#define tailleLabyrinthe 7

typedef char* string;
typedef short int bool; 


// y sur l'axe des horizontale et x sur l'axe verticale 
typedef struct position{
    int x;
    int y;
}position;

typedef struct tresor{
    position* piece;
    bool find;
    char affiche;
    
}tresor;

typedef struct joueur {
    position piece;
    int score;
    char affiche;
    string nom;
    tresor listeTresor[];
}joueur;

typedef struct tuile{
    int type;
    position posActuelle;
    tresor treasure;
    bool moove;
    int orientation;                // Orientation de base : 0  chaque +1 orientation indique une rotation de 90 degrès sur la droite 
}tuile;


void printElement(const char fond[tailleCase][tailleCase]);
bool init(void);
void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe]);


bool init(void)
{
    srand(time(NULL));
    const char typeT[tailleCase][tailleCase] = {{'#','#','#'},{'#',' ','#'},{'#',' ','#'}}; // type 0
    const char typeL[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ',' '},{'#','#','#'}}; // type 1
    const char typeI[tailleCase][tailleCase] = {{'#',' ','#'},{'#',' ','#'},{'#',' ','#'}}; // type 2
    tuile tableauTuiles[tailleLabyrinthe][tailleLabyrinthe];
    // afficher les elements 
    return true;
}


//  fonction de test 
void printElement(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe])
{ 
    for(int p = 0;p<tailleLabyrinthe;p++);
    {
        for(int v= 0;v<tailleLabyrinthe;v++)
        {
            // gerer l'orientation ici 
            // suite dans la fonction affichage case 
            for(int i = 0;i<tailleCase;i++)
            {
                for(int j = 0;j<tailleCase;j++)
                {
                    if(fond[i][j]==' ')
                        printf("   ");
                    else
                        printf("%c",fond[i][j]);
                }
                if(i!=2)
                    printf("\n");
            }
        }
        printf("\n");
    }
}

void affichageCase(tuile aAfficher)
{
    // comment faire pour affiche en fonction du type ???
    for(int i = 0;i<tailleCase;i++)
    {
        for(int j = 0;j<tailleCase;j++)
        {
            if(fond[i][j]==' ')
                printf("   ");
            else
                printf("%c",fond[i][j]);
        }
        if(i!=2)
            printf("\n");
    }
}


void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe])
{
    int tuileTnombreAvecTresor = 6;     // ICI type 0 pour check l'aleatoire    
    int tuileLnombreAvecTresor = 6;     // ICI type 1 pour check l'aleatoire
    int tuileLnombre = 10;              // ICI type 2 pour check l'aleatoire
    int tuileInombre = 12;              // ICI type 3 pour check l'aleatoire
    int typeTuileAleatoire;
    bool possible;
    for(int i = 0;i<tailleLabyrinthe;i++)
    {
        for(int j = 0;j<tailleLabyrinthe;j++)
        {
            tuile actuel;
            if(i==(0,2,4,6) || j==(0,2,4,6))
            {
                actuel.moove = false;
                actuel.orientation = 0;
                switch (i)
                {
                    case 0:
                        switch (j)
                        {
                        case 0:
                            actuel.type = 1;
                            actuel.orientation = 1;
                            // pas de tresor mais depart d'un joueur ici 
                            break;
                        case 2 || 4:
                            actuel.type = 0;
                            actuel.orientation = 0;
                            // tresor !!!
                            break;
                        case 6:
                            actuel.type = 1;
                            actuel.orientation = 2;
                            // tresor !!
                            break;
                        }
                        break;
                    case 2 :
                        actuel.type = 0;
                        switch (j)
                        {
                        case 0 || 2:
                            actuel.orientation = 3;
                            break;
                        case 4:
                            actuel.orientation = 0;
                            break;
                        case 6:
                            actuel.orientation = 1;
                            break;
                        }
                        break;
                    case 4 :
                        actuel.type = 0;
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
                            actuel.orientation = 0;
                            break;
                        }
                        break;
                    case 6 : 
                        switch (j)
                        {       
                        case 0:
                            actuel.type = 1;
                            actuel.orientation = 0;
                            break;
                        case 2 || 4: 
                            actuel.type = 0;
                            actuel.orientation = 2;
                        case 6:
                            actuel.type = 1;
                            actuel.orientation = 3;
                        }
                        break;
                }
                
            }
            else
            {
                actuel.moove = true;
                actuel.orientation = rand() % 4;
                // donner un type a chaque tuile en aleatoirement mais en faisant attetion que ce type de tuile est tjs dispo
                do{
                    possible = true;
                    typeTuileAleatoire = rand() % 4;
                    switch (typeTuileAleatoire)
                    {
                    case 0:
                        if(tuileTnombreAvecTresor == 0)
                            possible = false;
                        break;
                    case 1:
                        if(tuileLnombreAvecTresor==0)
                            possible =false;
                        break;
                    case 2:
                        if(tuileLnombre == 0)
                            possible = false;
                        break;
                    case 3:
                        if(tuileInombre==0)
                            possible = false;
                        break;
                    }
                }while(possible==false);
                switch (typeTuileAleatoire)
                {
                case 0:
                    actuel.type = 0;
                    // tresor !!!
                    break;
                case 1 : 
                    actuel.type = 1;
                    //tresor !!!
                    break;
                case 2 : 
                    actuel.type = 1;
                    break;
                case 3 :
                    actuel.type = 2;
                    break;
                }
            }
            position posActuel;
            posActuel.x = i;
            posActuel.y = j;
            actuel.posActuelle = posActuel;
            
        }
    }
}