//
//  Awale.h
//  Master1_Awale
//
//  Created by Chloé BENSOUSSAN on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#ifndef Awale_h
#define Awale_h

#include <stdio.h>

typedef struct {
    int plateau[10];    // Le plateau du jeu
    int grains_gagnes1; // Les grains récupérés par le joueur 1
    int grains_gagnes2; // Les grains récupérés par le joueur 2
} Awale;

void initialisation (Awale *a);

#endif /* Awale_h */
