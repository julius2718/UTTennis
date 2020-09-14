//
//  free.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/06.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "free.h"


//遺伝アルゴリズム用構造体
void free_individual_(info f,individual a_){
    int i;
    if(a_->list != NULL){
    for(i=0;i<f->people;i++){
        if(a_->list[i] != NULL)SAFE_FREE(a_->list[i]);
    }
    SAFE_FREE(a_->list);
    }
    SAFE_FREE(a_);
}

void free_individual(info f,individual* a){
    int i;
    for(i=0;i<N_GENE;i++){
        if(a[i] != NULL)free_individual_(f,a[i]);
    }
    SAFE_FREE(a);
}

void free_generation_(info f,generation g){
    free_individual(f,g->indi);
    SAFE_FREE(g->rank);
    SAFE_FREE(g);
}

void free_generation(info f,generation* g){
    int i;
    for(i=MAX_GENE;i>=0;i--){
        free_generation_(f,g[i]);
    }
    SAFE_FREE(g);
}

//評価関数用構造体
void free_court(info f,court x){
    SAFE_FREE(x->num_of_court);
    SAFE_FREE(x->number);
    SAFE_FREE(x->year);
    SAFE_FREE(x);
}

void free_player(info f,player me){
    int i;
    for(i=0;i<me->count;i++){
        SAFE_FREE(me->members[i]);
    }
    SAFE_FREE(me->day_list);
    SAFE_FREE(me->members);
    SAFE_FREE(me);
}

void free_detail(info f,detail det){
    int i;
    for(i=0;i<DAY;i++){
        free_court(f,det->courts[i]);
    }
    for(i=0;i<f->people;i++){
        free_player(f,det->players[i]);
    }
    SAFE_FREE(det->courts);
    SAFE_FREE(det->players);
    SAFE_FREE(det);
}

//基本データ用構造体

void free_score_data(score_data data){
    SAFE_FREE(data->p_inter);
    SAFE_FREE(data->p_short);
    SAFE_FREE(data->p_equ);
    SAFE_FREE(data->c_rank);
    SAFE_FREE(data->c_sum);
    SAFE_FREE(data);
}

void free_info(info f){
    int i;
    for(i=0;i<f->people;i++){
        SAFE_FREE(f->list[i]);
        SAFE_FREE(f->short_list[i]);
        SAFE_FREE(f->name[i]);
    }
    SAFE_FREE(f->count_can);
    SAFE_FREE(f->year);
    SAFE_FREE(f->list);
    SAFE_FREE(f->short_list);
    SAFE_FREE(f->name);
    free_score_data(f->score_data);
    SAFE_FREE(f);
}

void free_personal(int people,personal* plist){
    int i,p;
    i=0;p=0;
    while(p<people){
        if(plist[i]!=NULL){
            SAFE_FREE(plist[i]->list);
            SAFE_FREE(plist[i]->name);
            SAFE_FREE(plist[i]);
            p++;
        }
        i++;
    }
    SAFE_FREE(plist);
}
