#include "header.h"
#include "menu.h"
int main(int argc, char *argv[])
{
    if(argc==1)
        return 0;
        //execution de base du menu de jeu
    else if((int) *argv[1]==48)
    {
        string nomJoueurs[4] = {"Michael","Julien","Jean","Adam"};
        char listeTest[] = {'w','x','c','v'};
        tuile tableauLabyrinthe[tailleLabyrinthe][tailleLabyrinthe];
        joueur listJoueur[4];
        bool test =  init(4,nomJoueurs,listeTest,tableauLabyrinthe,listJoueur);
        printf("PAS ERREUR\n");
        inGame(4, nomJoueurs,listeTest);
    }
    else if((int) *argv[1]==49)
    {
        int nbJoueur = (int) *argv[2];
        char* nomJoueurs[nbJoueur];
        for(int i = 0;i<nbJoueur;i++)
        {
            nomJoueurs[i] = argv[i+2];
        }
        //return init(nbJoueur,nomJoueurs);
    }
    else if((int) *argv[1] == 50)
    {
        menuBase();
    }
    printf("\n");
    printf("%i\n", argc);
    return 0;
}