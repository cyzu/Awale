//
//  Utils.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 15/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include "Utils.h"

void verifieOption (int *joueur) {
	while ((*joueur)!=0  && (*joueur)!=1){
		printf("\n\n/!\\ Option invalide\n\n\n ");
		printf("Choisissez le mode de Jeu : \n      0 : l'ordinateur qui commence\n      1 : à vous de commencer\n      (pas de mode humain vs humain pour le moment)\n\nréponse : ");

		scanf("%d", joueur);
	}
}


void afficherJeu (EtatJeu *a) {
    printf("\n        (ordi)\n  1     2     3     4     5     6     7     8     9     10\n[%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d]      score : %d\n", a->plateau[0], a->plateau[1], a->plateau[2], a->plateau[3], a->plateau[4], a->plateau[5], a->plateau[6], a->plateau[7], a->plateau[8], a->plateau[9], a->grains_ordi);
    printf("[%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d] [%3d]      score : %d\n  20    19    18    17    16    15    14    13    12    11\n        (vous)\n\n\n", a->plateau[19], a->plateau[18], a->plateau[17], a->plateau[16], a->plateau[15], a->plateau[14], a->plateau[13], a->plateau[12], a->plateau[11], a->plateau[10], a->grains_humain);
}


void affichageDepart(){
    printf("\n\n°･*:.｡. BIENVENU DANS NOTRE JEU AWALÉ .｡.:*･ﾟ\n\n            Master 1 informatique\n      Université Nice Sophia-Antipolis\n\n\n");
    printf("     Andreina Wilhelm et Chloé Bensoussan\n\n\n");
    printf("Choisissez le mode de Jeu : \n      0 : l'ordinateur qui commence\n      1 : à vous de commencer\n      (pas de mode humain vs humain pour le moment)\n\nréponse : ");
}


void affichageFin(EtatJeu *partie){
    printf("\n\n LA PARTIE EST TERMINÉE ~☆\n\nAvec ce jeu :");
    afficherJeu(partie);

    if (partie->grains_ordi > partie->grains_humain)     printf("Le gagnant est  :  l'ordinateur...\n");
	else if (partie->grains_ordi < partie->grains_humain)   printf("Le gagnant est  :  vous! BRAVO!!\n");
    else printf("\nVous avez obtenu le meme score.\n");
}



void humainJoue(EtatJeu *partie, int case_choisie)
{
    int case_tmp = case_choisie;
    int nb_grains = partie->plateau[case_choisie];
    
    partie->plateau[case_choisie] = 0;

    while (nb_grains--) {
    	case_tmp++;
        
        if (case_tmp == NB_TOTAL_CASES) case_tmp = 0;
        if (case_tmp == case_choisie) case_tmp++;	// saute le trou sélectionné
        
        partie->plateau[case_tmp]++;
    }
    
    // dans le plateau de l'ordi
    if(case_tmp < MOITIE_CASES) {
    	while (case_tmp-- && ((nb_grains = partie->plateau[case_tmp]) == 2 || nb_grains == 3)) {
    		partie->grains_humain += nb_grains;
    		partie->plateau[case_tmp] = 0;
		}
    }
    partie->joueur = !partie->joueur;
}



void ordiJoue(EtatJeu *partie)
{
	clock_t tic = clock();

	int case_choisie = valeurMinMax(partie, 0, 0, MIN_NUM, MAX_NUM);

    clock_t toc = clock();
    printf("\n\nElapsed: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    

    printf("**** L'ordinateur a choisi la case %d ↓\n", case_choisie + 1);


    int case_tmp = case_choisie;
    int nb_grains = partie->plateau[case_choisie];

    partie->plateau[case_choisie] = 0;
    
    while (nb_grains--) {
    	case_tmp++;
        
        if (case_tmp == NB_TOTAL_CASES) case_tmp = 0;
        if (case_tmp == case_choisie) case_tmp++;	// saute le trou sélectionné
        
        partie->plateau[case_tmp]++;
    }
    
    // dans le plateau du joueur
    while ((case_tmp-- - MOITIE_CASES) && ((nb_grains = partie->plateau[case_tmp]) == 2 || nb_grains == 3)) {
    	partie->grains_ordi += nb_grains;
    	partie->plateau[case_tmp] = 0;
	}
    partie->joueur = !partie->joueur;
}



void jouer(EtatJeu *partie)
{
    int case_;
    
    while (!positionFinale(partie, partie->joueur))
    {
        afficherJeu(partie);
        if (partie->joueur == 0) ordiJoue(partie);
        else {
            printf("A vous de jouer ! Quel case choisissez-vous ?   ");
            scanf("%d", &case_);
            while (!(case_ <= NB_TOTAL_CASES && case_ > MOITIE_CASES)){
                printf("\n/!\\ Cette case ne vous appartient pas !\nChoisissez à partir de votre plateau :  ");
                
                scanf("%d", &case_);
            }
            
            while (partie->plateau[case_ -1] <= 0){
                printf("\n/!\\ Il n'y a pas de graine sur cette case !\nChangez :  ");
                
                scanf("%d", &case_);
            }
            case_ = case_ - 1;
            humainJoue(partie, case_);
        }
        
    }
    affichageFin(partie);
}
