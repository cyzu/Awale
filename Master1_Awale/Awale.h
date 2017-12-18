//
//  Awale.h
//  Master1_Awale
//
//  Created by Chloé BENSOUSSAN on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#ifndef Awale_h
#define Awale_h

#define PROFONDEUR_MAX 9
#define GRAINS_MAX 80

#define NB_TOTAL_CASES 20
#define MIN_NUM	-500
#define MAX_NUM 500

typedef struct {
    int plateau[NB_TOTAL_CASES];    // Le plateau du jeu. [0, 4] humain (joueur 1). [5, 9] ordi (joueur 2)
    int grains_humain;  // Les grains récupérés par le joueur 1
    int grains_ordi;    // Les grains récupérés par le joueur 2
    
    int joueur;         // == 1 si c'est au joueur 2 de jouer, == 0 quand c'est le joueur 1 (ordinateur)
} EtatJeu;


void initialisation (EtatJeu *a, int joueur);

/* Fonctions utilisées par min-max */
int positionFinale(EtatJeu *partie, const int joueur);
static inline int evaluation(EtatJeu const *partie);
static inline int coupValide(EtatJeu const *partie, const int case_);
void jouerCoup(EtatJeu *partie_suivante, EtatJeu const *partie, int const joueur, int const case_);

int valeurMax(int const prof, int const tableau[NB_TOTAL_CASES/2]);
int valeurMin(int const prof, int const tableau[NB_TOTAL_CASES/2]);

int valeurMinMax(EtatJeu *partie, int const joueur, int const profondeur, int const min, int const max);

#endif /* Awale_h */
