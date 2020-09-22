//
//  first_generation.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "first_generation.h"


generation first_generation(info f){
    int i;
    generation g = new_generation(f);
    g->gene = 0;
    for(i=0;i<N_GENE;i++){
        g->indi[i] = random_individual(f);
        g->indi[i]->gene = g->gene;
        g->indi[i]->number = i;
        scoring(f,g->indi[i]);
    }
    rank_build(f,g);
    return g;
}

