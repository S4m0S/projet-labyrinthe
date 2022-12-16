#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct position{
    int x;
    int y;
};

typedef struct tresor{
    position* piece;
    bool find;
    char affiche;
};

typedef struct {
    position* piece;
    bool trouve;
    char affichage;
    
};