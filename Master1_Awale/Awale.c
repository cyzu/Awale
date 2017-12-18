//
//  Awale.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include <math.h>
#include <unistd.h>
#include "Awale.h"

/* Initialisation de la structure */
void initialisation (EtatJeu *a, int joueur){
    int i = 0;
    for (i = 0; i < NB_TOTAL_CASES; i++) a->plateau[i] = 4;
    
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
    if (joueur == 0) {
        if (partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] + partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[9] == 0){
            
            /* le joueur 1 récupère toutes les graines restantes */
            partie->grains_humain += partie->plateau[10] + partie->plateau[11] + partie->plateau[12] + partie->plateau[13] + partie->plateau[14] + partie->plateau[15] + partie->plateau[16] + partie->plateau[17] + partie->plateau[18] + partie->plateau[19];
            
            partie->plateau[10]= 0;
            partie->plateau[11]= 0;
            partie->plateau[12]= 0;
            partie->plateau[13]= 0;
            partie->plateau[14]= 0;
            partie->plateau[15]= 0;
            partie->plateau[16]= 0;
            partie->plateau[17]= 0;
            partie->plateau[18]= 0;
            partie->plateau[19]= 0;
            
            return 1;
        }
    }
    else if (partie->plateau[10] + partie->plateau[11] + partie->plateau[12] + partie->plateau[13] + partie->plateau[14] + partie->plateau[15] + partie->plateau[16] + partie->plateau[17] + partie->plateau[18] + partie->plateau[19] == 0){
        /* le joueur 2 (ordi) récupère toutes les graines restantes */
        
        partie->grains_ordi += partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] + partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[9];
        
        partie->plateau[0]= 0;
        partie->plateau[1]= 0;
        partie->plateau[2]= 0;
        partie->plateau[3]= 0;
        partie->plateau[4]= 0;
        partie->plateau[5]= 0;
        partie->plateau[6]= 0;
        partie->plateau[7]= 0;
        partie->plateau[8]= 0;
        partie->plateau[9]= 0;
        
        return 1;
    }
    
    
    /* Etat boucle (il n'y a plus qu'une graine chez chaque joueur sans pouvoir être prises */
    if ((partie->plateau[0] + partie->plateau[1] + partie->plateau[2] + partie->plateau[3] + partie->plateau[4] + partie->plateau[5] + partie->plateau[6] + partie->plateau[7] + partie->plateau[8] + partie->plateau[9]) == 1 &&
        (partie->plateau[10] + partie->plateau[11] + partie->plateau[12] + partie->plateau[13] + partie->plateau[14] + partie->plateau[15] + partie->plateau[16] + partie->plateau[17] + partie->plateau[18] + partie->plateau[19]) == 1){
        int case_humain = -1, case_ordi = -1;
        
         /* Récupérer les numéros de cases n'ayant qu'une seule graine */
        int i = 0;
        for (i = 0; i < NB_TOTAL_CASES/2; i++) {
            if (partie->plateau[i] == 1) case_ordi = i;
        }
        for (i = NB_TOTAL_CASES/2; i < NB_TOTAL_CASES; i++) {
            if (partie->plateau[i] == 1) case_humain = i;
        }
        
        if (case_humain - case_ordi == NB_TOTAL_CASES/2) return 1;
    }
    return 0;
}



int evaluation(EtatJeu const *partie, int joueur) {//, int const case_){
   // return partie->grains_recup[case_];
   // return abs(partie->grains_humain - partie->grains_ordi);


    int halfSize = NB_TOTAL_CASES/2;

    // Nombre de trous que l'ordi peut utiliser pour prendre 2 et 3 cailloux
    // Nombre de trous d'ordi qui peuvent arriver au cote d'humain
    // Nombre de trous avec plus de 20 cailloux
    // Nombre de trous vide
    int ordi_cap_deux = 0;
    int ordi_cap_trois = 0;
    int ordi_arri_hum = 0;
    int ordi_vingt = 0;
    int ordi_vide = 0;

    for (int i = 0; i < halfSize ; i++) {
    	int graines = partie->plateau[i];
		int cycles = graines / NB_TOTAL_CASES;
		int trou_arrive = (i + graines + cycles) % NB_TOTAL_CASES;

		if(halfSize <= trou_arrive && trou_arrive < NB_TOTAL_CASES){
			if(partie->plateau[trou_arrive] == 1) ordi_cap_deux++;
			else if(partie->plateau[trou_arrive] == 2) ordi_cap_trois++;
			ordi_arri_hum++;
		}

		if(partie->plateau[i] >= NB_TOTAL_CASES) ordi_vingt++;
		else if (partie->plateau[i] == 0) ordi_vide++;
	}


    // Nombre de trous que l'humain peut utiliser pour prendre 2 et 3 cailloux
    // Nombre de trous d'humain qui peuvent arriver au cote d'ordi
    // Nombre de trous avec plus de 20 cailloux
    // Nombre de trous vide
    int hum_cap_deux = 0;
    int hum_cap_trois = 0;
    int hum_arri_ordi = 0;
    int hum_vingt = 0;
    int hum_vide = 0;

    for (int i = halfSize; i < NB_TOTAL_CASES ; i++) {
    	int graines = partie->plateau[i];
		int cycles = graines / NB_TOTAL_CASES;
		int trou_arrive = (i + graines + cycles) % NB_TOTAL_CASES;

		if(0 <= trou_arrive && trou_arrive < halfSize) {
			if(partie->plateau[trou_arrive] == 1) hum_cap_deux++;
			else if(partie->plateau[trou_arrive] == 2) hum_cap_trois++;
			hum_arri_ordi++;
		}

		if(partie->plateau[i] >= NB_TOTAL_CASES) hum_vingt++;
		else if (partie->plateau[i] == 0) hum_vide++;
	}

    int result = hum_vide * 1.0 +
				ordi_vide * 0.67 +
				ordi_cap_deux * 0.93 +
				ordi_cap_trois * 0.93 +
				hum_vingt * 0.06 +
				ordi_vingt * 0.93 +
				hum_arri_ordi * 0.13 +
				ordi_arri_hum * 0.87 +
				partie->grains_humain * 0.13 +
				partie->grains_ordi * 0.60 +
				hum_cap_deux * 0.06 +
    			hum_cap_trois * 0.20;

    return result;
}



/* Vérifie que la case_ peut être jouée par le joueur :
    - return 1 si c'est possible,
    - return 0 sinon
 */
int coupValide(EtatJeu *partie, const int case_){
    return (partie->plateau[case_] > 0);
}



void jouerCoup(EtatJeu *partie_suivante, EtatJeu const *partie, int joueur, int case_){
    
    // copier partie dans partie_suivante
    int i = 0;
    for (i = 0; i < NB_TOTAL_CASES ; i++) {
        partie_suivante->plateau[i] = partie->plateau[i];
    }
    partie_suivante->grains_humain = partie->grains_humain;
    partie_suivante->grains_ordi = partie->grains_ordi;
    partie_suivante->joueur = joueur;
    // fin copier
    
    int nb_graine = partie->plateau[case_];
    i = nb_graine;
    int case_tmp = case_; // connaitre la case de départ
    
    partie_suivante->plateau[case_] = 0; // prendre les pions de la case_
    for(i = nb_graine; i > 0; i--){
        case_tmp ++;
        
        if (case_tmp > NB_TOTAL_CASES - 1) case_tmp = 0;
        if (case_tmp == case_) case_tmp ++;
        
        
        partie_suivante->plateau[case_tmp] ++;
    }
    /* Récupération des graines si on peut en prendre */
    if (joueur == 0){
        for (i = case_tmp; i < NB_TOTAL_CASES && i >= NB_TOTAL_CASES/2 && (partie_suivante->plateau[i] == 2 || partie_suivante->plateau[i] == 3); i--) {
            partie_suivante->grains_ordi += partie_suivante->plateau[i];
            partie_suivante->plateau[i] = 0;
        }
    }
    else {
        for (i = case_tmp; i < NB_TOTAL_CASES/2 && i >= 0 && (partie_suivante->plateau[i] == 2 || partie_suivante->plateau[i] == 3); i--) {
            partie_suivante->grains_humain += partie_suivante->plateau[i];
            partie_suivante->plateau[i] = 0;
        }
    }    
}




/* Retourne la valeur maximale du tableau */
int valeurMax(int const prof, int const tableau[NB_TOTAL_CASES/2]) {
    int maximum = 0;

    if (prof == 0) {
        for (int i = 0; i < NB_TOTAL_CASES/2; i++) {
        	if ((tableau[i] > tableau[maximum] || tableau[maximum] > GRAINS_MAX) && tableau[i] <= GRAINS_MAX) maximum = i;
        }
    }
    else {
        for (int i = 0; i < NB_TOTAL_CASES/2; i++) {
            if ((tableau[i] > tableau[maximum] || tableau[maximum] > GRAINS_MAX) && tableau[i] <= GRAINS_MAX) maximum = tableau[i];
        }
    }
    return maximum;
}


/* Retourne la valeur minimale du tableau */
int valeurMin(int const prof, int const tableau[NB_TOTAL_CASES/2]) {
    int minimum = 0;

    if (prof == 0) {
        for (int i = 0; i < NB_TOTAL_CASES/2; i++) {
        	if ((tableau[i] < tableau[minimum] || tableau[minimum] < 0) && tableau[i] > 0) minimum = i;
        }
    } else {
        for (int i = 0; i < NB_TOTAL_CASES/2; i++) {
            if ((tableau[i] < minimum || tableau[minimum] < 0) && tableau[i] > 0) minimum = tableau[i];
        }
    }
    return minimum;
}



/* Algotithme Min-max pour déterminer le meilleur coup à jouer */
int valeurMinMax(EtatJeu *partie_actuelle, int joueur, int profondeur, int min, int max) {
    EtatJeu coup_suivant;
    int tableau_valeurs[NB_TOTAL_CASES/2];
    
    /* Initialisation tableau_valeurs[] */
    for (int j = 0; j < NB_TOTAL_CASES/2; j++) tableau_valeurs[j] = 0;
    

    /* Conditions d'arrêt de la récurrence :
        - la partie est terminée
        - on a atteint la profondeur maximale
     */
    if (positionFinale(partie_actuelle, joueur)) {
        //retourner GRAINS_MAX si ordi gagne, -GRAINS_MAX si humain gagne, -1 si partie nulle
        
        if (partie_actuelle->grains_humain > partie_actuelle->grains_ordi) return GRAINS_MAX;
        else if (partie_actuelle->grains_ordi > partie_actuelle->grains_humain) return -GRAINS_MAX;
        else return 0;
    }
    
    else if (profondeur == PROFONDEUR_MAX){
        return evaluation(partie_actuelle, joueur);
        // dans un premier temps l'évaluation sera la
        // difference du nb de pions pris
    }


/*
    int case_correct = joueur * NB_TOTAL_CASES/2;
    int i = 0;
    for(i = 0; i < NB_TOTAL_CASES/2; i++){

        if (coupValide(partie_actuelle, i + case_correct)){
            // on joue le coup i a partir de la position
            // pos_courante et on met le rÈsultat
            // dans pos_next
            jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);
            // pos_next devient la position courante, et on change le joueur
            tableau_valeurs[i] = valeurMinMax(&coup_suivant, (joueur + 1) % 2, profondeur + 1, 0, 0);
        }
        else {
            if (joueur == 0) tableau_valeurs[i] = -500;
            else tableau_valeurs[i] = 500;
        }
    }
*/


    int val;
    int case_correct = joueur * NB_TOTAL_CASES/2;

    if(joueur == 0) { //MAX
		val = min;

        for(int i = 0; i < NB_TOTAL_CASES/2; i++) {
	        if (coupValide(partie_actuelle, i + case_correct)) {
	            // on joue le coup i a partir de la position
	            // pos_courante et on met le rÈsultat
	            // dans pos_next
	            jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);

	            // pos_next devient la position courante, et on change le joueur
				int valEnfant = valeurMinMax(&coup_suivant, (joueur + 1) % 2, profondeur + 1, val, max);//, i + case_correct);

				if(valEnfant > val)	{
					val = valEnfant;
					tableau_valeurs[i] = val;
				}

				if(val > max) return max;
	        }
	        else {
	        	tableau_valeurs[i] = MIN_NUM;
	        }
	    }

    }
    else { // MIN
		val = max;

		for(int i = 0; i < NB_TOTAL_CASES/2; i++) {
	        if (coupValide(partie_actuelle, i + case_correct)) {
	            // on joue le coup i a partir de la position
	            // pos_courante et on met le rÈsultat
	            // dans pos_next
	            jouerCoup(&coup_suivant, partie_actuelle, joueur, i + case_correct);

				// pos_next devient la position courante, et on change le joueur
				int valEnfant = valeurMinMax(&coup_suivant, (joueur + 1) % 2, profondeur + 1, min, val);//, i + case_correct);

				if(valEnfant < val) {
					val = valEnfant;
					tableau_valeurs[i] = val;
				}

				if(val < min) return min;
	        }
	        else {
	        	tableau_valeurs[i] = MAX_NUM;
	        }
	    }
	}
    int case_choisie = 0;
    if (joueur == 0) case_choisie = valeurMax(profondeur, tableau_valeurs);
    else  case_choisie = valeurMin(profondeur, tableau_valeurs);

    return case_choisie;
}

