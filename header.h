#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef char* string;


typedef struct {
    position* piece;
    bool trouve;
    char affichage;
    
}tresor;


typedef struct {
    tresor* listeTresor[];
    position posJ;
    int trouve;
    string nom;
    char affichage; 
}







