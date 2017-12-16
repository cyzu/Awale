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
#include "Awale.h"

void afficherJeu (EtatJeu *a);
void affichageDepart();

void humainJoue (EtatJeu *a, int trou_choisie);
void ordiJoue(EtatJeu *partie);

void jouer(EtatJeu *partie);

#endif /* Utils_h */
