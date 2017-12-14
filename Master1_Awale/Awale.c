//
//  Awale.c
//  Master1_Awale
//
//  Created by Chloé 雪乃 BENSOUSSAN 下村 on 14/12/2017.
//  Copyright © 2017 Chloé BENSOUSSAN. All rights reserved.
//

#include "Awale.h"

void initialisation (Awale *a){
    int i = 0;
    for (i = 0; i < 10; i++) a->plateau[i] = 4;
    
    a->grains_gagnes1 = 0;
    a->grains_gagnes2 = 0;
}
