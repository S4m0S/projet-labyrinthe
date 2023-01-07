#include <stdio.h>
#include <string.h>
//#include "header.h"
/*
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
}*/




void menuLancement(void);
void menuBase(void)
{
    bool running = true;
    int input;
    system("cls"); // ou cls si windows
    do{
        printf("   1. Lancer une partie\n   2. Charger une partie\n   3. Modifiez les parametre\n   4. Quitter \n   Choisisez une option : ");
        scanf("%i",&input);
        while(getchar()!='\n');
        switch (input)
        {
        case 1:
            menuLancement();
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
        system("cls"); // ou cls sur windows
    }while(running);
}


void menuLancement(void)
{
    bool pass;
    int nbJoueur;
    do
    {
        printf("Combien y aura-t-il de joueurs : ");
        scanf("%i",&nbJoueur);
        //while(getchar()!='\n');
    }while(nbJoueur<2 || nbJoueur>4);
    system("cls");
    string nomJoueur[4];
    char pionJoueur[4];
    for(int i = 0;i<nbJoueur;i++)
    {
        printf("Quel est le nom du joueur numero %i : ",i+1);
        scanf("%s",&nomJoueur[i]);
        while(getchar()!='\n');
        do{
        printf("Quel sera votre pions : ");
        scanf("%c",&pionJoueur[i]);
        while(getchar()!='\n');
        }while(pionJoueur[i]=='#');
        system("cls");
    }
    
    inGame(nbJoueur,nomJoueur,pionJoueur);
    
    
}

void chargerLesPartis(void)
{
    bool running = true;
    //charger les partis
    int nbPartis = 0;
    date listeDate[10];
    int choix;
    while(running)
    {
        if(nbPartis==0)
        {
            printf("Aucune partis n'est actuellement disponible, commencer en une nouvelle !");
            while(getchar()!='\n');
            running = false;
        }
        else
        {
            for(int i = 0;i<nbPartis;i++)
            {
                printf("Partie numero %i, vous y avez jouez le %i/%i/%i à %i:%i:%i \n",i+1,listeDate[i].day,listeDate[i].month,listeDate[i].year,listeDate[i].hours,listeDate[i].minutes,listeDate[i].seconds);
            }
            printf("Quelle partie souhaitez vous reprendre ? (0 pour quitter) ");
            scanf("%i",&choix);
        }
    }
}