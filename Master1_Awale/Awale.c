//
//  Awale.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include <stdlib.h>
#include "Awale.h"

/* Initialisation de la structure */
void initialisation (EtatJeu *a, int const joueur) {
    for(int i =0; i< NB_TOTAL_CASES; i ++) a->plateau[i] = 4;
    
    a->grains_humain = 0;
    a->grains_ordi = 0;
    
    a->joueur = joueur;
}


 /* Cherche si la partie actuelle est une position finale :
    - plus de graines chez un joueur
    - un joueur a récupéré plus de la moitié des graines
    - on ne peut plus prendre de graines (états boucles)

 Retourne 1 si c'est une position finale, 0 sinon.
*/
int positionFinale(EtatJeu *partie, const int joueur){
    // Un des joueurs a récupéré plus de la moitié des graines
	int moitie_grains = GRAINS_MAX/2;
    if (partie->grains_humain >= moitie_grains || partie->grains_ordi >= moitie_grains) return 1;
    

    int sum_ordi = partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] + partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[9];
    int sum_humain = partie->plateau[10] + partie->plateau[11] + partie->plateau[12] + partie->plateau[13] + partie->plateau[14] + partie->plateau[15] + partie->plateau[16] + partie->plateau[17] + partie->plateau[18] + partie->plateau[19];


    // Vérifie qu'il n'y a plus de graines chez le joueur
    if (joueur == 0) {
    	if(sum_ordi == 0) return 1;
    }
    else if (sum_humain == 0) return 1;
    

    // Etat boucle (il n'y a plus qu'une graine chez chaque joueur sans pouvoir être prises
    if (sum_ordi == 1 && sum_humain == 1)
    {
    	// Récupérer les numéros de cases n'ayant qu'une seule graine
        int case_humain = -1, case_ordi = -1;
        int i;
        int case_limit = NB_TOTAL_CASES - 1;

        i = MOITIE_CASES;
        while(i--) {
        	if(partie->plateau[i] == 1) {
        		case_ordi = i;
        		break;
        	}

        	if (partie->plateau[case_limit - i] == 1) {
				case_humain = i;
				break;
			}
        }

        if (case_humain - case_ordi == MOITIE_CASES) return 1;
    }
    return 0;
}


inline int evaluation(EtatJeu const *partie) {
    return abs(partie->grains_ordi - partie->grains_humain);
}


/*	Vérifie que la case_ peut être jouée par le joueur :
    - return 1 si c'est possible,
    - return 0 sinon */
inline int coupValide(EtatJeu const *partie, const int case_){
    return partie->plateau[case_] > 0;
}


void jouerCoup(EtatJeu *partie_suivante, EtatJeu const *partie, int const joueur, int const case_choisie){
    
    // copier partie dans partie_suivante
	int i = NB_TOTAL_CASES + 1;
	while(i--) partie_suivante->plateau[i] = partie->plateau[i];

    partie_suivante->grains_humain = partie->grains_humain;
    partie_suivante->grains_ordi = partie->grains_ordi;
    partie_suivante->joueur = joueur;
    // fin copier
    
    
    int case_tmp = case_choisie;
    int nb_grains = partie->plateau[case_choisie];

    partie_suivante->plateau[case_choisie] = 0;

    while (nb_grains--) {
    	case_tmp++;
        
        if (case_tmp == NB_TOTAL_CASES) case_tmp = 0;
        if (case_tmp == case_choisie) case_tmp++;	// saute le trou sélectionné
        
        partie_suivante->plateau[case_tmp]++;
    }

    // Récupération des graines si on peut en prendre
    case_tmp++;
    if (joueur == 0)
    {
		while ((case_tmp - MOITIE_CASES) >= 0 && ((nb_grains = partie_suivante->plateau[case_tmp]) == 2 || nb_grains == 3)) {
			partie_suivante->grains_ordi += nb_grains;
			partie_suivante->plateau[case_tmp] = 0;
		}
    }
    else if (case_tmp < MOITIE_CASES)
    {
        while ((nb_grains = partie_suivante->plateau[case_tmp]) == 2 || nb_grains == 3) {
            partie_suivante->grains_humain += nb_grains;
            partie_suivante->plateau[case_tmp] = 0;
            case_tmp--;
        }
    }
}


/* Retourne la valeur maximale du tableau*/
int valeurMax(int const prof, int* const tableau) {
    int maximum = 0;

    if (prof == 0) {
		for(int i = 0; i < MOITIE_CASES; i++) {
        	if (tableau[i] > tableau[maximum]) maximum = i;
        }
    }
    else {
    	for(int i = 0; i < MOITIE_CASES; i++) {
            if (tableau[i] > maximum) maximum = tableau[i];
        }
    }
    return maximum;
}

/* Retourne la valeur minimale du tableau */
int valeurMin(int const prof, int* const tableau) {
    int minimum = 0;

    if (prof == 0) {
    	for(int i = 0; i < MOITIE_CASES; i++) {
        	if (tableau[i] < tableau[minimum]) minimum = i;
        }
    } else {
    	for(int i = 0; i < MOITIE_CASES; i++) {
            if (tableau[i] < minimum) minimum = tableau[i];
        }
    }
    return minimum;
}


/* Algotithme Min-max pour déterminer le meilleur coup à jouer*/
int valeurMinMax(EtatJeu *partie_actuelle, int const joueur, int const profondeur, int const min, int const max) {
    int tableau_valeurs[MOITIE_CASES];
    
    // Initialisation tableau_valeurs[]
    tableau_valeurs[0] = 0;
    tableau_valeurs[1] = 0;
    tableau_valeurs[2] = 0;
    tableau_valeurs[3] = 0;
    tableau_valeurs[4] = 0;
    tableau_valeurs[5] = 0;
    tableau_valeurs[6] = 0;
    tableau_valeurs[7] = 0;
    tableau_valeurs[8] = 0;
    tableau_valeurs[9] = 0;
    

    /* Conditions d'arrêt de la récurrence :
      - la partie est terminée
      - on a atteint la profondeur maximale */
    if (positionFinale(partie_actuelle, joueur)) {
        if (partie_actuelle->grains_humain > partie_actuelle->grains_ordi) return -GRAINS_MAX;
        else if (partie_actuelle->grains_ordi > partie_actuelle->grains_humain) return GRAINS_MAX;
        else return 0;
    }
    else if (profondeur == PROFONDEUR_MAX) return evaluation(partie_actuelle);
    
    EtatJeu coup_suivant;
    int val, valEnfant, i;
    int case_correct = joueur * MOITIE_CASES;

    if(joueur == 0) { //MAX
		val = min;

        for(i = 0; i < MOITIE_CASES; i++) {
	        if (coupValide(partie_actuelle, i + case_correct))
	        {
                jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);
                valEnfant = valeurMinMax(&coup_suivant, !joueur, profondeur + 1, val, max);

				if(valEnfant > val)	{
					val = valEnfant;
					tableau_valeurs[i] = val;
				}
				if(val > max) return max;
	        }
	        else tableau_valeurs[i] = MIN_NUM;
	    }
        return valeurMax(profondeur, tableau_valeurs);
    }
    else	// MIN
    {
		val = max;

		for(i = 0; i < MOITIE_CASES; i++) {
	        if (coupValide(partie_actuelle, i + case_correct))
	        {
	            jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);
				valEnfant = valeurMinMax(&coup_suivant, !joueur, profondeur + 1, min, val);

				if(valEnfant < val) {
					val = valEnfant;
					tableau_valeurs[i] = val;
				}
				if(val < min) return min;
	        }
	        else tableau_valeurs[i] = MAX_NUM;
	    }
		return valeurMin(profondeur, tableau_valeurs);
	}
}

