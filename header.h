#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

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
    bool oove;
    int orientation;
}tuile;
