//
//  main.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Awale.h"

int main (int argc, char *argv[]) {
    
    EtatJeu partie;
    initialisation(&partie);
    
    afficher_jeu(&partie);
    
    partie.plateau[5] = 0;
    partie.plateau[6] = 0;
    partie.plateau[0] = 0;
    partie.plateau[4] = 10;
    humain_joue(&partie, 4);
    
    afficher_jeu(&partie);
    
    return 0;
    
    /*TODO : vérifier après l'appel de coupValide, case_ ne change pas de valeur ! */
    
    return 0;
}
