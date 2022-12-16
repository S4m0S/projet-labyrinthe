#include <string.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct tresor{
    position* piece;
    bool find;
    char affiche;
};

typedef struct joueur {
    position* piece;
    bool trouve;
    char affichage;
    
};