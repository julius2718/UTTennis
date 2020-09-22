//
//  next_generation.c
//  practice_member
//
//  Created by 長澤達也 on 2019/11/05.
//  Copyright © 2019 長澤達也. All rights reserved.
//

#include "next_generation.h"

individual select_individual(info f,generation g){
    //rankに基づいた確率で親を選ぶ(良い個体ほど選ばれやすい)
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


individual selection(info f,generation g){
    //選択法による次世代新個体の作成.部分的突然変異を入れるのもあり.
    individual a,parent;
    parent = select_individual(f,g);
    a = copy_individual(f,parent);
    return a;
}

individual crossover(info f,generation g){
    //交叉法による次世代新個体の作成.
    int i; //j,d1,d2(旧で使用)
    double t; //sum,total(旧で使用)
    double p;
    individual a = new_individual(f);
    //親を2つ選択.選択法を利用
    individual p1,p2;
    p1 = select_individual(f,g);
    p2 = select_individual(f,g);
    while(1){
        //親被りしない
        if(p1->number!=p2->number)break;
        p2 = select_individual(f,g);
    }
    //親の評価値の優位性p;
    p = (double)p1->score/(p1->score+p2->score);
    //人ごとにどちらの親の日程にするか決める.p_randであらたな練習日程になる.
    for(i=0;i<f->people;i++){
        t = (double)rand()/RAND_MAX;
        if(t<CROSSOVER){
            random_list(f,a->list[i],i);
        }else if(t<p){
            memcpy(a->list[i],p1->list[i],DAY*sizeof(int));
        }else{

            memcpy(a->list[i],p2->list[i],DAY*sizeof(int));
        }
    }
    scoring(f,a);
    /*以下test用出力
    printf("親は以下の2つです\n");
    print_individual(f,p1);
    print_individual(f,p2);
    printf("交叉による子供は以下です\n");
    print_individual(f,a);
    */
    return a;
}

individual mutation(info f,generation g){
    //突然変異による次世代新個体の作成
    individual a = random_individual(f);
    scoring(f,a);
    return a;
}

individual next_generation_(info f,generation g){
    //新個体の作成方法の抽選
    individual new_indi;
    double t = (double)rand()/RAND_MAX;
    if(t<SELECTION){
        //"選択"による新個体の作成
        new_indi = selection(f,g);
    }else if(t<SELECTION + MUTATION){
        //"突然変異"による新個体の作成
        new_indi = mutation(f,g);
    }else if(t<1){
        //"交叉"による新個体の作成
        new_indi = crossover(f,g);
    }else{
        printf("error in next_generation.\n 抽選値tを確認してください.\n");
        exit(EXIT_FAILURE);
    }
    return new_indi;
}

generation next_generation(info f,generation g){
    int i;
    generation g_next = new_generation(f);
    g_next->gene = g->gene +1;
    //現行世代の最高値を次世代の始めに残す
    g_next->indi[0] = copy_individual(f,g->indi[g->max_indi]);
    g_next->indi[0]->gene = g_next->gene;
    g_next->indi[0]->number = 0;
    //2-N_GENEまでの個体を生成
    for(i=1;i<N_GENE;i++){
        g_next->indi[i] = next_generation_(f,g);
        g_next->indi[i]->gene = g_next->gene;
        g_next->indi[i]->number = i;
    }
    //scoreに基づく相対順位rankを計算
    rank_build(f,g_next);
    return g_next;
}

generation next_generation_random(info f,generation g){
    //最高個体の引き継ぎ以外が全て突然変異の新個体
    int i;
    generation g_next = new_generation(f);
    g_next->gene = g->gene +1;
    //現行世代の最高値を次世代の始めに残す
    g_next->indi[0] = copy_individual(f,g->indi[g->max_indi]);
    g_next->indi[0]->gene = g_next->gene;
    g_next->indi[0]->number = 0;
    //2-N_GENEまでの個体を生成
    for(i=1;i<N_GENE;i++){
        g_next->indi[i] = mutation(f,g);
        g_next->indi[i]->gene = g_next->gene;
        g_next->indi[i]->number = i;
    }
    rank_build(f,g_next);
    return g_next;
}
