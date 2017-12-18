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
#include "Utils.h"

int main (int argc, char *argv[]) {
    EtatJeu partie;
    int premier;
    
    affichageDepart();
    scanf("%d", &premier);
    printf("\n\n");
    
    initialisation(&partie, premier);
    
    /*partie.plateau[0] = 3;
    partie.plateau[1] = 2;
    partie.plateau[2] = 2;
    partie.plateau[3] = 1;
    partie.plateau[4] = 11;
    partie.plateau[5] = 4;
    partie.plateau[6] = 4;
    partie.plateau[7] = 6;
    partie.plateau[8] = 4;
    partie.plateau[9] = 2;*/
    
    jouer(&partie);
    
    return 0;
}
