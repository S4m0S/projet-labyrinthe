#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define tailleCase 3
#define tailleLabyrinthe 7
#define typeTuileEnT 500
#define typeTuileEnL 501
#define typeTuileEnI 502

typedef char* string;
typedef short int bool; 


// y sur l'axe des horizontale et x sur l'axe verticale 
typedef struct position{
    int x;
    int y;
}position;

typedef struct tresor{
    position* piece;        // addresse de la position de la pièce sur laquelle ce trouve le tresor
    bool find;              // le tresor a-t-il déja etait trouvé
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
bool init(void);
void initialisationTuiles(tuile tableauTuile[tailleLabyrinthe][tailleLabyrinthe]);
void affichageCase(const char fond[3][3],int k,int orientation);




bool init(void)         // fonction d'initialisation du jeu une fois celle-ci effectuer on peut commencer a jouer 
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
    printf("orientation gauche : %i; orientation droite : %i\n",tableauTuiles[0][0].orientation,tableauTuiles[0][6].orientation);
    printElement(tableauTuiles,typeTuile);
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
    // comment faire pour affiche en fonction du type ???
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
            if(fond[j][k]==' ')
                printf(" ");
            else
                printf("%c",fond[j][k]);
            }
            break;
        case 2:
            for(int j = 0;j<tailleCase;j++)
            {
            if(fond[2-k][j]==' ')
                printf(" ");
            else
                printf("%c",fond[2-k][j]);
            }
            break;
        case 3:
            for(int j = 2;j<0;j--)
            {
            if(fond[j][k]==' ')
                printf(" ");
            else
                printf("%c",fond[j][k]);
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
    int tuileLnombre = 100;              // ICI type 2 pour check l'aleatoire  : aléatoire de celle-ci
    int tuileInombre = 12;              // ICI type 3 pour check l'aleatoire
    int typeTuileAleatoire;             // Vairable pour faire un choix entre les 4 variables ci-dessus
    bool possible;                      // check si la pièce aleatoire est bien disponible 
    int checkValue[4] = {0,2,4,6};      // valeur pour lesquels le tes pièces seront immobiles
    bool checkImmobile;
    for(int i = 0;i<tailleLabyrinthe;i++)
    {
        for(int j = 0;j<tailleLabyrinthe;j++)
        {
            
            tuile actuel;           // initialisationd de la tuile actuelle, celle-ci sera ensuite inserer dans le tableau
            checkImmobile = false;
            // faire un test qui doit donner checkImmobile = true si la tuile est une tuile basique (0,0) (0,2) (0,4) ...
            if(checkImmobile==true)    // on regarde si la pièce est une pièce qui ne peut pas bouger
            {
                // le test ci dessus est peut etre pas bon en fait
                printf("Passage par les tuiles de base; i = %i ; j = %i\n",i,j); 
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
                        case 2 || 4:
                            actuel.type = typeTuileEnT;
                            actuel.orientation = 0;
                            // tresor !!!
                            break;
                        case 6:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 2;
                            // tresor !!
                            break;
                        }
                        break;
                    case 2 :
                        actuel.type = typeTuileEnT;
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
                            actuel.orientation = 0;
                            break;
                        }
                        break;
                    case 6 : 
                        switch (j)
                        {       
                        case 0:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 0;
                            break;
                        case 2 || 4: 
                            actuel.type = typeTuileEnT;
                            actuel.orientation = 2;
                        case 6:
                            actuel.type = typeTuileEnL;
                            actuel.orientation = 3;
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
                            tuileTnombreAvecTresor--;
                        }
                        break;
                    case 1:
                        if(tuileLnombreAvecTresor!=0)
                        {
                            possible =true;
                            actuel.type = typeTuileEnL;
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
            position posActuel;
            posActuel.x = i;
            posActuel.y = j;
            actuel.posActuelle = posActuel;
            tableauTuile[i][j] = actuel;
        }
    }
}