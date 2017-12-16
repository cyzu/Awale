//
//  Awale.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include <math.h>
#include "Awale.h"

/* Initialisation de la structure */
void initialisation (EtatJeu *a, int joueur){
    int i = 0;
    for (i = 0; i < 10; i++) a->plateau[i] = 4;
    
    a->grains_humain = 0;
    a->grains_ordi = 0;
    
    a->joueur = joueur;
}

/* Cherche si la partie actuelle est une position finale :
    - plus de graines chez un joueur
    - un joueur a récupéré plus de la moitié des graines
    - on ne peut plus prendre de graines (états boucles)
 
 ** Retourne 1 si c'est une position finale, 0 sinon.
 */
int positionFinale(EtatJeu *partie, const int joueur){
    /* Un des joueurs a récupéré plus de la moitié des graines */
    if (partie->grains_humain > GRAINS_MAX/2 || partie->grains_ordi > GRAINS_MAX/2) return 1;
    
    /* Vérifie qu'il n'y a plus de graines chez le joueur */
    if (joueur == 0){
        if (partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[8] == 0){
            /* le joueur 1 récupère toutes les graines restantes */
            partie->grains_humain += partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4];
            
            return 1;
        }
    }
    else if (partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] == 0){
        /* le joueur 2 (ordi) récupère toutes les graines restantes */
        partie->grains_ordi += partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[9];
        
        return 1;
    }
    
    
    /* Etat boucle (il n'y a plus qu'une graine chez chaque joueur sans pouvoir être prises */
    if ((partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[8]) == 1 &&
        (partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4]) == 1){
        int case_humain = -1, case_ordi = -1;
        
         /* Récupérer les numéros de cases n'ayant qu'une seule graine */
        int i = 0;
        for (i = 0; i < 5; i++) {
            if (partie->plateau[i] == 1) case_humain = i;
        }
        for (i = 5; i < 10; i++) {
            if (partie->plateau[i] == 1) case_ordi = i;
        }
        
        if (case_ordi - case_humain == 5) return 1;
    }
    return 0;
}

int evaluation(EtatJeu const *partie){
    return abs(partie->grains_humain - partie->grains_ordi);
}

/* Vérifie que la case_ peut être jouée par le joueur :
    - return 1 si c'est possible,
    - return 0 sinon
 */
int coupValide(EtatJeu *partie, const int case_){
    //printf("$$ (joueur %d) $$ coup valide [%d] ?  %d\n", partie->joueur, case_, partie->plateau[case_] > 0);
    return (partie->plateau[case_] > 0);
}

void jouerCoup(EtatJeu *partie_suivante, EtatJeu *partie, int joueur, int case_){
    
    // copier partie dans partie_suivante?
    int i = 0;
    for (i = 0; i < 10; i++) {
        partie_suivante->plateau[i] = partie->plateau[i];
    }
    partie_suivante->grains_humain = partie->grains_humain;
    partie_suivante->grains_ordi = partie->grains_ordi;
    // fin copier
    
    int nb_graine = partie->plateau[case_];
    i = nb_graine;
    int case_tmp = case_; // connaitre la case de départ
    
    partie_suivante->plateau[case_] = 0; // prendre les pions de la case_
    for(i = nb_graine; i > 0; i--){
        case_tmp ++;
        
        if (case_tmp > 9) case_tmp = 0;
        if (case_tmp == case_) case_tmp ++;
        
        
        partie_suivante->plateau[case_tmp] ++;
    }
    /* Récupération des graines si on peut en prendre */
    if (joueur == 0){
        for (i = case_tmp; i <= 4 && i >= 0 && (partie_suivante->plateau[i] == 2 || partie_suivante->plateau[i] == 3); i--) {
            partie_suivante->grains_ordi += partie_suivante->plateau[i];
            partie_suivante->plateau[i] = 0;
        }
    }
    else {
        for (i = case_tmp; i <= 9 && i >= 5 && (partie_suivante->plateau[i] == 2 || partie_suivante->plateau[i] == 3); i--) {
            partie_suivante->grains_humain += partie_suivante->plateau[i];
            partie_suivante->plateau[i] = 0;
        }
    }
}

/* Retourne la valeaur maximale du tableau */
int valeurMax(int const tableau[5]){
    int maximum = tableau[0];
   
    int i = 0;
    for (i = 0; i < 5; i++) {
        if (tableau[i] > maximum && tableau[i] < GRAINS_MAX && tableau[i] >= 0) maximum = tableau[i];
    }
    return maximum;
}

/* Retourne la valeur minimale du tableau */
int valeurMin(int const tableau[5]){
    int minimum = tableau[0];
    
    int i = 0;
    for (i = 0; i < 5; i++) {
        if (tableau[i] < minimum && tableau[i] >= 0 && tableau[i] < GRAINS_MAX) minimum = tableau[i];
    }
    return minimum;
}

/* Algotithme Min-max pour déterminer le meilleur coup à jouer */
int valeurMinMax(EtatJeu *partie_actuelle, int joueur, int profondeur){
    EtatJeu coup_suivant;
    int plateau[5];
    
    /* Conditions d'arrêt de la récurrence :
        - la partie est terminée
        - on a atteint la profondeur maximale
     */
    if (positionFinale(partie_actuelle, joueur)){
        //retourner GRAINS_MAX si ordi gagne, -GRAINS_MAX si humain gagne, -1 si partie nulle
        
        if (partie_actuelle->grains_humain > partie_actuelle->grains_ordi) return -GRAINS_MAX;
        else if (partie_actuelle->grains_ordi > partie_actuelle->grains_humain) return GRAINS_MAX;
        else return -1;
    }
    
    else if (profondeur == PROFONDEUR_MAX){
        return evaluation(partie_actuelle);
        // dans un premier temps l'évaluation sera la
        // difference du nb de pions pris
    }
    
    int case_correct = (1 - joueur) * 5;
    int i = 0;
    for(i = 0; i < 5; i++){
        
        if (coupValide(partie_actuelle, i + case_correct)){
            // on joue le coup i a partir de la position
            // pos_courante et on met le rÈsultat
            // dans pos_next
            jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);
            // pos_next devient la position courante, et on change le joueur
            plateau[i] = valeurMinMax(&coup_suivant, (joueur + 1) % 2, profondeur + 1);
        }
        else {
            if (joueur == 0) plateau[i] = -100;
            else plateau[i] = +100;
        }
        printf("____plateau[%d] = %d\n",i, plateau[i]);
    }
    
    int grains = 0;
    
    if (joueur == 0) grains = valeurMax(plateau);
    else  grains = valeurMin(plateau);
    
    printf("$$$$$$ case choisi ? %d, joueur %d\n", grains, partie_actuelle->joueur);
    return grains;
}

