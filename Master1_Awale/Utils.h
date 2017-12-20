//
//  Utils.h
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 15/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#ifndef Utils_h
#define Utils_h

#include <stdio.h>
#include <time.h>
#include "Awale.h"

void verifieOption (int *joueur);
void afficherJeu (EtatJeu const *a);
void affichageDepart();
void affichageFin(EtatJeu const *partie, int const resultat);

void humainJoue (EtatJeu *a, int const case_choisie);
void ordiJoue(EtatJeu *partie);

void jouer(EtatJeu *partie);

#endif /* Utils_h */
