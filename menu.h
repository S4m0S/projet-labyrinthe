#include <stdio.h>
#include <string.h>
#include "header.h"

void menuInitial(){//soit on fait la declaration du choix ici
    int choix;//soit on déclare ici
    do{
    system("cls");//on est obligé de mettre ça ?? L'usage de cette commande doit être limité, car c'est laid dans un code et plutôt couteux en ressources.
    printf("1. Nouvelle partie\n 2.Credits/Regles du jeu\n 3.Quitter\n");
    scanf("%d",&choix);}
    while(choix<1&&choix>3);
    system("cls");
    switch(choix){
        case 1:
            char listeNomsJoueurs, listePionsJoueurs;
            joueur listeJoueurs;
            DemarrageMenu(listeNomsJoueurs,listeJoueurs,listePionsJoueurs);
            //EnJeux();
            break;
        case 2:
            {
            printf("Regles du jeu:\nLe Labyrinthe est un jeu de plateau comprenant 2 a 4 joueurs.\nChaque joueur possède une liste de tresors
            qu'il doit aller chercher dans un labyrinthe de 49 tuiles.\n Pour cela, chacun leur tour, les joueurs ont la possibilite de deplacer 
            une rangee de tuiles et de placer une tuile au bout de cette rangee.\n Le joueur peut faire pivoter cette tuile. Enfin, le joueur peut 
            deplacer son pion d'autant de case qu' il veut,tant qu' il suit un chemin.\n Le premier joueur qui recupere tout ses tresors gagne la partie.\n
            Credits: Adda Michael - El Haj Jean - Hogommat Julien - Nasreddine Adam\n");
            }       
            break;
        case 3:
            break;
            //jsp trop quoi mettree 
    }
}





void menuBase(void)
{
    bool running = true;
    int input; 
    do{
        printf("   1. Lancer une partie\n   2. Charger une partie\n   3. Modifiez les parametre\n   4. Quitter \n   Choisisez une option : ");
        scanf("%i",&input);
        switch (input)
        {
        case 1:
            //fonction pour lancer la partie
            break;
        case 2:
            //fonction pour charger une partie
            break;
        case 3 : 
            //fonction pour modifiez les parametre
            break;
        case 4:
            running = false;
            break;
        default:
            printf("Mauvaise réponse dommage...");
            break;
        }
        system("clear"); // ou cls sur windows
    }while(running);
}


void menuLancement(void)
{
    bool pass;
    int nbJoueur;
    do
    {
        printf("Combien y aura-t-il de joueuers ?");
        scanf("%i",&nbJoueur);
    }while(nbJoueur<2 && nbJoueur>4);
    string nomJoueur[nbJoueur];
    char pionJoueur[nbJoueur];
    for(int i = 0;i<nbJoueur;i++)
    {
        printf("Quel est le nom du joueur numero %i : ",i);
        scanf("%s",nomJoueur[i]);
        do{
        printf("Quel sera votre pions ?");
        scanf("%c",pionJoueur[i]);
        }while(pionJoueur[i]=='#');
    }
    inGame(nbJoueur,nomJoueur,pionJoueur);
    
    
}