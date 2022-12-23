#include <stdio.h>
#include <string.h>
#include "header.h"

void menuInitial(){//soit on fait la declaration du choix ici
    int choix;//soit on déclare ici
    do{
    printf("1. Nouvelle partie\n 2.Credits/Regles du jeu\n 3.Quitter\n");
    scanf("%d",&choix);}
    while(choix<1&&choix>3);
    switch(choix){
        case 1:
            //lance une nouvelle partie
    
        case 2:
            //

        case 3:
            //jsp trop quoi mettre 
    }
}

void DemarrageMenu(char listeNomsJoueurs[],joueur listeJoueurs[],char listePionJoueurs[]){
    char listeRepresentation[4] = {'♥','♦','♣','♠'};
    int nbJoueurs;
    char nom[50];
    int nbPion;
    printf("saisir le nombre de joueurs:\n");
    scanf("%d",&nbJoueurs);
    for(int i=0;i<nbJoueurs;i++){
        printf("donner le nom du joueur %d",i);
        fgets(nom,50,stdin);
        listeNomsJoueurs[i]=*nom;
        printf("saisir votre pion: 1.♥\n2.♦\n3.♣\n4.♠\n");
        scanf("%d",&nbPion);
        switch(nbPion){
            case 1:
                
        }    

    }


}