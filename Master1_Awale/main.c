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
    
    jouer(&partie);
    
    return 0;
}
