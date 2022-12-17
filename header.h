#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define tailleCase 3
#define tailleG

typedef char* string;
typedef short int bool; 

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
    int orientation;
}tuile;


void printElement(char fond[tailleCase][tailleCase]);
bool init(void);


bool init(void)
{
    const char typeT[tailleCase][tailleCase] = {{'#','#','#'},{'#',' ','#'},{'#',' ','#'}};
    const char typeL[tailleCase][tailleCase] = {{'#',' ','#'},{' ',' ',' '},{'#',' ','#'}};
    const char typeI[tailleCase][tailleCase] = {{'8',' ','#'},{'#',' ','#'},{'#',' ','#'}};
    printElement(typeI);
    return true;
}


//  fonction de test 
void printElement(const char fond[tailleCase][tailleCase])
{
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