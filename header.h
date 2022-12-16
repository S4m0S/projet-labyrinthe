#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef char* string;

typedef struct position{
    int x;
    int y;
};

typedef struct tresor{
    position* piece;
    bool find;
    char affiche;
    
};

typedef struct joueur {
    position piece;
    int score;
    char affiche;
    string nom;
    tresor listeTresor[];


};

typedef struct tuile{
    int type;
    position posActuelle;
    tresor treasure;
    bool oove;
    int orientation;
};
