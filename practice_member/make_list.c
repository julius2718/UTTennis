//
//  random_member.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "make_list.h"

individual new_individual(info f){
    //individualの初期化
    //リストの初期値は全て0
    //その他の初期値は-1
    int i,j;
    individual a;
    NEW(a,1);
    NEW(a->list,f->people);
    for(i=0;i<f->people;i++){
        NEW(a->list[i],DAY);
        for(j=0;j<DAY;j++){
            a->list[i][j] = 0;
        }
    }
    a->gene = -1;
    a->number = -1;
    a->score = -1;
    return a;
}

generation new_generation(info f){
    //generationの初期化
    //indiの初期値はNULL,rankの初期値は0
    //geneとmax_indiの初期値は-1
    generation g;
    int i;
    NEW(g,1);
    NEW(g->indi,N_GENE);
    NEW(g->rank,N_GENE);
    g->gene = -1;
    g->max_indi = -1;
    for(i=0;i<N_GENE;i++){
        g->indi[i] = NULL;
        g->rank[i] = 0;
    }
    return g;
}

void random_list(info f,int* list,int people){
    //"people"個人の練習日程を制約の中でランダムに組む
    //結果はlistに格納
    int n = f->count_prac[people];  //残りの入る練習回数
    int c = f->count_can[people];   //固定以外に可能な練習回数
    int cf = f->count_fix[people];  //固定された練習回数
    int d,day;
    for(d=0;d<DAY;d++){
        //固定された練習をlistに追加する.
        if(f->list[people][d]==-1){
            list[d]=1;
            cf--;
            n--;
        }
    }
    while(n>0){
        //可能練習の中でランダムに1つ選んで1にする.nが0になるまで続ける
        //0~cで値をランダムにdayを決定→可能日程の中でday番目の日程に練習を入れる
        day = rand()%c;
        for(d=0;d<DAY;d++){
            if(f->list[people][d] == 1){
                if(day<=0 && list[d]!=1){
                    list[d]=1;
                    n--;
                    c--;
                    break;
                }
                day--;
            }
        }
    }
}

individual random_individual(info f){
    //個体の練習日程を最低制約条件(f->list)のなかでランダム生成.
    int i;
    individual a = new_individual(f);
    for(i=0;i<f->people;i++){
        random_list(f,a->list[i],i);
    }
    return a;
}

individual copy_individual(info f,individual a){
    //individualのscoreとlistを値渡しする
    int i;
    individual a_copy = new_individual(f);
    a_copy->score = a->score;
    for(i=0;i<f->people;i++){
        memcpy(a_copy->list[i],a->list[i],DAY*sizeof(int));
    }
    return a_copy;
}

