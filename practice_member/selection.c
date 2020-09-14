//
//  selection.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "selection.h"

individual select_individual(info f,generation g){
    //ルーレット法により親を選ぶ
    int i;
    individual a = g->indi[0];
    double p = (double)rand()/RAND_MAX;
    double sum = 0;
    for(i=0;i<N_GENE;i++){
        sum += g->rank[i];
        if(sum>=p){
            a = g->indi[i];
            return a;
        }
    }
    printf("error in select_individual.抽選値pを確認してください.\n");
    return a;
}


