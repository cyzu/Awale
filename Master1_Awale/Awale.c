//
//  Awale.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include "Awale.h"

/* Initialisation de la structure */
void initialisation (EtatJeu *a){
    int i = 0;
    for (i = 0; i < 10; i++) a->plateau[i] = 4;
    
    a->grains_humain = 0;
    a->grains_ordi = 0;
    
    a->joueur = 1;
}

/* Cherche si la partie actuelle est une position finale :
    - plus de graines chez un joueur
    - un joueur a récupéré plus de la moitié des graines
    - on ne peut plus prendre de graines (états boucles)
 
 ** Retourne 0 si c'est une position finale, -1 sinon.
 */
int positionFinale(EtatJeu *partie, const int joueur){
    /* Un des joueurs a récupéré plus de la moitié des graines */
    if (partie->grains_humain > GRAINS_MAX/2 || partie->grains_ordi > GRAINS_MAX/2) return 0;
    
    /* Vérifie qu'il n'y a plus de graines chez le joueur */
    if (joueur == 0){
        if (partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[8] == 0){
            /* le joueur 1 récupère toutes les graines restantes */
            partie->grains_humain += partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4];
            
            return 0;
        }
    }
    else if (partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] == 0){
        /* le joueur 2 (ordi) récupère toutes les graines restantes */
        partie->grains_ordi += partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[9];
        
        return 0;
    }
    
    
    /* Etat boucle (il n'y a plus qu'une graine chez chaque joueur sans pouvoir être prises */
    if (partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[8] == 1 &&
        partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] == 1){
        int case_humain = -1, case_ordi = -1;
        
         /* Récupérer les numéros de cases n'ayant qu'une seule graine */
        int i = 0;
        for (i = 0; i < 5; i++) {
            if (partie->plateau[i] == 1) case_humain = i;
        }
        for (i = 5; i < 10; i++) {
            if (partie->plateau[i] == 1) case_ordi = i;
        }
        
        if (case_ordi - case_humain == 5) return 0;
    }
    return -1;
}

/* Vérifie que la case_ peut être jouée par le joueur :
    - return 0 si c'est possible,
    - return -1 sinon
 */
inline int coupValide(EtatJeu const *partie, const int case_){
    if (partie->plateau[case_] <= 0) return -1;
    return 0;
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
inline int valeurMax(int const tableau[5]){
    int maximum = tableau[0];
   
    int i = 0;
    for (i = 0; i < CASE_PAR_PERSONNE; i++) {
        if (tableau[i] > maximum) maximum = tableau[i];
    }
    return maximum;
}

/* Retourne la valeur minimale du tableau */
inline int valeurMin(int const tableau[5]){
    int minimum = tableau[0];
    
    int i = 0;
    for (i = 0; i < CASE_PAR_PERSONNE; i++) {
        if (tableau[i] < minimum) minimum = tableau[i];
    }
    return minimum;
}

/* Algotithme Min-max pour déterminer le meilleur coup à jouer */
int valeurMinMax(EtatJeu *partie_actuelle, int joueur, int profondeur){
    /* joueur == 0 si l'ordi joue, 1 sinon */
    EtatJeu coup_suivant;
    int plateau[5];
    
    /* Conditions d'arrêt de la récurrence :
        - la partie est terminée
        - on a atteint la profondeur maximale
     */
    if (positionFinale(partie_actuelle, joueur) == 0){
        //retourner GRAINS_MAX si ordi gagne, -GRAINS_MAX si humain gagne, 0 si partie nulle
        
        if (partie_actuelle->grains_humain > partie_actuelle->grains_ordi) return 1;
        else if (partie_actuelle->grains_ordi > partie_actuelle->grains_humain) return 2;
        else return 0;
    }
    
    if (profondeur == PROFONDEUR_MAX){
        return evaluation(partie_actuelle, joueur, profondeur);
        // dans un premier temps l'évaluation sera la
        // difference du nb de pions pris
    }
    
    int case_correct = (1 - joueur) * 5;
    int i = 0;
    for(i = 0; i < CASE_PAR_PERSONNE; i++){
        
        if (coupValide(partie_actuelle, i + case_correct) == 0){
            // on joue le coup i a partir de la position
            // pos_courante et on met le rÈsultat
            // dans pos_next
            jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);
            // pos_next devient la position courante, et on change le joueur
            plateau[i] = valeurMinMax(&coup_suivant, (joueur + 1) % 2, profondeur + 1);
        }
        else {
            // ?????
            if (joueur == 0) plateau[i] = -100;
            else plateau[i] = +100;
        }
    }
    
    int grains = 0;
    
    if (joueur == 0) grains = valeurMin(plateau);
    else  grains = valeurMax(plateau);
    
    return grains;
}







/********************/
/*      HUMAIN      */
/********************/



void afficher_jeu (EtatJeu *a) {
    //printf("\n\n\nTour de jeu : %s\n\n",(jouer==0?"vous":"CPU"));
    
    printf("%3d %3d %3d %3d %3d      score : %d		ordi\n", a->plateau[5], a->plateau[6], a->plateau[7], a->plateau[8], a->plateau[9], a->grains_ordi);
    printf("%3d %3d %3d %3d %3d      score : %d		humain\n\n", a->plateau[4], a->plateau[3], a->plateau[2], a->plateau[1], a->plateau[0], a->grains_humain);
}


// VERIFIE avant appeler: Le joueur sélectionne un trou dans sa rangée.
void humain_joue(EtatJeu *a, int trou_choisie) {
    
    int trou = trou_choisie;
    int nb_grains = a->plateau[trou_choisie];
    a->plateau[trou_choisie] = 0;
    
    for (int i = 0; i < nb_grains; i++) {
        trou++;
        
        if (trou > 9) trou = 0;
        if (trou == trou_choisie) trou++;	// saute le trou sélectionné
        
        a->plateau[trou]++;
    }
    
    // dans le plateau de l'ordi
    for(int i = trou; i > 4 && (a->plateau[i] == 2 || a->plateau[i] == 3); i--) {
        a->grains_humain += a->plateau[i];
        a->plateau[i] = 0;
    }
}

