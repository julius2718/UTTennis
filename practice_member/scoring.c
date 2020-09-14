//
//  scoring.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "scoring.h"


void scoring(info f,individual a){
    //個体aの評価関数
    //練習スコアと個人スコアの合計
    double score=0;
    detail det = detail_of_individual(f, a);
    score += court_score(f,det);
    score += personal_score(f,a,det);
    a->score = score;
    free_detail(f,det);
}

void rank_build(info f,generation g){
    //g->rankとg->max_indiを求める
    //g->rank:scoreから正規化した値
    //g->max_indi:score最大のindividualのnumber
    int i,max_i = 0;
    double sum = 0;
    double min_score = 0;
    for(i=0;i<N_GENE;i++){
        if(min_score > g->indi[i]->score) min_score = g->indi[i]->score;
        if(g->indi[max_i]->score < g->indi[i]->score) max_i = i;
    }
    for(i=0;i<N_GENE;i++){
        //最低点が0になるように補正
        sum += g->indi[i]->score - min_score;
    }
    for(i=0;i<N_GENE;i++){
        g->rank[i] = (g->indi[i]->score - min_score)/sum;
    }
    g->max_indi = max_i;
}

