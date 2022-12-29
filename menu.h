#include <stdio.h>
#include <string.h>
#include "header.h"

void menuInitial(){//soit on fait la declaration du choix ici
    int choix;//soit on déclare ici
    do{
    system("cls");
    printf("1. Nouvelle partie\n 2.Credits/Regles du jeu\n 3.Quitter\n");
    scanf("%d",&choix);}
    while(choix<1&&choix>3);
    system("cls");
    switch(choix){
        case 1:
            char listeNomsJoueurs[], listePionsJoueurs[];
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
            //jsp trop quoi mettre 
    }
}

void DemarrageMenu(char listeNomsJoueurs[],joueur listeJoueurs[],char listePionJoueurs[]){
    char listeRepresentation[4] = {'♥','♦','♣','♠'};
    int nbJoueurs;
    char nom[50];
    int nbPion;
    system("cls");
    printf("saisir le nombre de joueurs:\n");
    scanf("%d",&nbJoueurs);
    for(int i=0;i<nbJoueurs;i++){
        system("cls");
        printf("donner le nom du joueur %d",i);
        fgets(nom,50,stdin);
        listeNomsJoueurs[i]=*nom;
        printf("saisir votre pion: 1.♥\n2.♦\n3.♣\n4.♠\n");
        scanf("%d",&nbPion);
        switch(nbPion){
            case 1:
                listePionJoueurs[i]=listeRepresentation[0];
                break;
            case 2:
                listePionJoueurs[i]=listeRepresentation[1];
                break;
            case 3:
                listePionJoueurs[i]=listeRepresentation[2];
                break;
            case 4:
                listePionJoueurs[i]=listeRepresentation[3];
                break;
                
        }
        //pour la couleur vu qu'on la pas mis dans la structure joueur jsp    

    }
    initialisationJouers(nbJoueurs,listeNomsJoueurs,listeJoueurs,listePionJoueurs);
}

bool ReperageQuit(){
    string renvoi;
    printf("presser q pour quitter:");
    fgets(renvoi,100,stdin);
    if (renvoi=='q'||renvoi=='Q'){
        return false;
    }
    else{
        return true;
    }
}//on le met au debut de chaque tour et si cest vrai on lance sinon on arrete