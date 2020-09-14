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


generation take_over_generation(info f,generation g){
    //そのままgeneを引き継ぐ
    int i;
    generation g_next = new_generation(f);
    g->gene = 0;
    for(i=0;i<N_GENE;i++){
        g_next->indi[i] = copy_individual(f,g->indi[i]);
        g_next->indi[i]->gene = 0;
        g_next->indi[i]->number = i;
    }
    rank_build(f,g_next);
    return g_next;
}
